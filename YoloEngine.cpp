#include "pch.h"
#include "YoloEngine.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

YoloEngine::YoloEngine()
    : env_(ORT_LOGGING_LEVEL_WARNING, "VisionEngine"),
    session_(nullptr),
    inputWidth_(0),
    inputHeight_(0)
{
}

YoloEngine::~YoloEngine()
{
    if (session_)
    {
        delete session_;
        session_ = nullptr;
    }
}

bool YoloEngine::LoadModel(const std::string& modelPath)
{
    try
    {
        Ort::SessionOptions opts;
        opts.SetIntraOpNumThreads(1);
        opts.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

        // 尝试使用宽字符字符串
        std::wstring wModelPath(modelPath.begin(), modelPath.end());
        session_ = new Ort::Session(env_, wModelPath.c_str(), opts);

        // 读取输入尺寸
        Ort::TypeInfo inputTypeInfo = session_->GetInputTypeInfo(0);
        auto tensorInfo = inputTypeInfo.GetTensorTypeAndShapeInfo();
        auto dims = tensorInfo.GetShape();

        // dims: [1, 3, H, W]
        inputHeight_ = static_cast<int>(dims[2]);
        inputWidth_ = static_cast<int>(dims[3]);

        return true;
    }
    catch (const Ort::Exception& e)
    {
        std::cout << "LoadModel failed: " << e.what() << std::endl;
        return false;
    }
}

void YoloEngine::Preprocess(const std::string& imagePath,
    std::vector<float>& inputTensor,
    int& inputW,
    int& inputH)
{
    cv::Mat img = cv::imread(imagePath);
    cv::Mat resized;

    inputW = inputWidth_;
    inputH = inputHeight_;

    cv::resize(img, resized, cv::Size(inputW, inputH));
    resized.convertTo(resized, CV_32F, 1.0 / 255.0);

    // NHWC → NCHW
    inputTensor.resize(1 * 3 * inputH * inputW);

    int idx = 0;
    for (int c = 0; c < 3; c++)
    {
        for (int y = 0; y < inputH; y++)
        {
            for (int x = 0; x < inputW; x++)
            {
                inputTensor[idx++] = resized.at<cv::Vec3f>(y, x)[c];
            }
        }
    }
}

void YoloEngine::Postprocess(const float* outputData,
    size_t elementCount,
    YoloResult& result)
{
    // 每个 OBB: 7 个数
    const int stride = 7;
    int boxCount = static_cast<int>(elementCount / stride);

    result.box_count = 0;

    for (int i = 0; i < boxCount && result.box_count < MAX_OBB_COUNT; i++)
    {
        const float* p = outputData + i * stride;

        OBBBox& box = result.boxes[result.box_count++];
        box.cx = p[0];
        box.cy = p[1];
        box.w = p[2];
        box.h = p[3];
        box.angle = p[4];   // 弧度
        box.conf = p[5];
        box.cls = static_cast<int>(p[6]);
    }
}

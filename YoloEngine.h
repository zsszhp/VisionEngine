#pragma once
#include <string>
#include <vector>
#include <onnxruntime_cxx_api.h>
#include "VisionTypes.h"

class YoloEngine
{
public:
    YoloEngine();
    ~YoloEngine();

    // 加载 ONNX 模型
    bool LoadModel(const std::string& modelPath);

    // 对单张图片做 OBB 推理
    bool Infer(const std::string& imagePath, YoloResult& result);

private:
    void Preprocess(const std::string& imagePath,
        std::vector<float>& inputTensor,
        int& inputW,
        int& inputH);

    void Postprocess(const float* outputData,
        size_t elementCount,
        YoloResult& result);

private:
    Ort::Env env_;
    Ort::Session* session_;
    Ort::AllocatorWithDefaultOptions allocator_;

    int inputWidth_;
    int inputHeight_;
};

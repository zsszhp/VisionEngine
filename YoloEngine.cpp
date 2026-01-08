#include "pch.h"
#include "YoloEngine.h"
#include <iostream>

YoloEngine::YoloEngine()
    : env_(ORT_LOGGING_LEVEL_WARNING, "VisionEngine"),
    session_(nullptr)
{
}

bool YoloEngine::LoadModel(const std::string& modelPath)
{
    try
    {
        Ort::SessionOptions session_options;
        session_options.SetIntraOpNumThreads(1);
        session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

        // 将 std::string 转换为宽字符字符串，或使用正确的参数类型
        session_ = new Ort::Session(env_, modelPath.c_str(), session_options);
        return true;
    }
    catch (const Ort::Exception& e)
    {
        std::cout << "ONNX Load Failed: " << e.what() << std::endl;
        return false;
    }
}
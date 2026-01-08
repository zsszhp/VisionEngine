#pragma once
#include <string>
#include <onnxruntime_cxx_api.h>

class YoloEngine
{
public:
    YoloEngine();
    bool LoadModel(const std::string& modelPath);

private:
    Ort::Env env_;
    Ort::Session* session_;
};

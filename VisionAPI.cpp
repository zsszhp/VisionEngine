#include "pch.h"
#include "VisionAPI.h"
#include "Logger.h"
#include "OBBCropper.h"
#include "HalconDecoder.h"
#include "BoxProcessor.h"
#include "YoloEngine.h"
#include "VisionResult.h"

#include <opencv2/opencv.hpp>
#include <cstring>
#include <mutex>

// ===============================
// 内部全局状态（线程安全）
// ===============================
namespace
{
    bool g_initialized = false;
    std::mutex g_initMutex;
}

// ===============================
// 初始化
// ===============================
int Vision_Init(const char* logPath)
{
    std::lock_guard<std::mutex> lock(g_initMutex);

    if (g_initialized)
        return VISION_OK;

    if (logPath && std::strlen(logPath) > 0)
    {
        Logger::Init(logPath);
        Logger::Info("Vision_Init OK");
    }

    g_initialized = true;
    return VISION_OK;
}

// ===============================
// 主流程
// ===============================
int Vision_ProcessImage(
    const char* imagePath,
    VisionResult* result)
{
    // ---------- 参数检查 ----------
    if (!imagePath || !result)
        return VISION_ERR_NULL_POINTER;

    // 清空输出（防止 C# 读到脏数据）
    result->success = 0;
    result->confidence = 0.0f;
    std::memset(result->code, 0, sizeof(result->code));

    try
    {
        // ---------- 读图 ----------
        cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
        if (image.empty())
        {
            Logger::Error("Image load failed");
            return VISION_ERR_LOAD_IMAGE;
        }

        // ---------- ⚠️ 示例 OBB（后续接 YOLO） ----------
        OBBBox box;
        box.cx = image.cols * 0.5f;
        box.cy = image.rows * 0.5f;
        box.w = image.cols * 0.5f;
        box.h = image.rows * 0.25f;
        box.angle = 0.0f;
        box.cls = 0;
        box.conf = 1.0f;

        // ---------- 裁剪 ----------
        cv::Mat roi = OBBCropper::Crop(image, box);
        if (roi.empty())
        {
            Logger::Error("OBB crop failed");
            return VISION_ERR_CROP_FAIL;
        }

        // ---------- 解码 ----------
        if (!HalconDecoder::Decode(roi, *result))
        {
            Logger::Error("Decode failed");
            return VISION_ERR_DECODE_FAIL;
        }

        // ---------- 成功 ----------
        result->success = 1;
        Logger::Info("Vision_ProcessImage OK");
        return VISION_OK;
    }
    catch (...)
    {
        Logger::Error("Unhandled exception");
        return VISION_ERR_INTERNAL;
    }
}

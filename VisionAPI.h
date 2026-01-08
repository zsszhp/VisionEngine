#pragma once
#include "VisionResult.h"

#ifdef _WIN32
#define VISION_API __declspec(dllexport)
#else
#define VISION_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief 初始化视觉引擎（可重复调用）
     * @param logPath 日志路径（可为 nullptr，表示不写日志）
     */
    VISION_API int Vision_Init(const char* logPath);

    /**
     * @brief 处理一张图片
     * @param imagePath 输入图片路径（必须存在）
     * @param result 输出结果（调用方分配）
     * @return VisionErrorCode
     */
    VISION_API int Vision_ProcessImage(
        const char* imagePath,
        VisionResult* result);

#ifdef __cplusplus
}
#endif

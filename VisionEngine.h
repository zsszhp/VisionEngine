#pragma once

#include "VisionTypes.h"

#ifdef VISIONENGINE_EXPORTS
#define VISION_API __declspec(dllexport)
#else
#define VISION_API __declspec(dllimport)
#endif

extern "C"
{
    /**
     * @brief 运行一次视觉算法（当前为假实现，后续接 YOLO / Halcon）
     * @param imagePath 输入图片路径
     * @param result 输出结果结构体（由 C++ 填充）
     * @return 0 = 成功，非 0 = 错误码
     */
    VISION_API int Vision_Run(
        const char* imagePath,
        VisionResult* result
    );
}

#pragma once

/**
 * @brief 单个条码识别结果
 */
struct VisionResult
{
    int   success;              // 1 成功 / 0 失败
    char  code[256];            // 条码字符串
    float confidence;           // 置信度（可扩展）
};
#pragma once

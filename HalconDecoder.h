#pragma once
#include <opencv2/opencv.hpp>
#include "VisionResult.h"

/**
 * @brief Halcon 条码解码封装
 */
class HalconDecoder
{
public:
    /**
     * @brief 解码 ROI 中的条码
     * @param roi 输入 ROI（BGR）
     * @param result 输出识别结果
     * @return true 成功 / false 失败
     */
    static bool Decode(const cv::Mat& roi, VisionResult& result);
};

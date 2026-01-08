#pragma once
#include <opencv2/opencv.hpp>
#include "VisionTypes.h"

/**
 * @brief OBB 裁剪与旋转模块（等价 Python warpAffine + getRectSubPix）
 */
class OBBCropper
{
public:
    /**
     * @brief 根据 OBB 裁剪旋转 ROI
     * @param src 原始图像
     * @param box OBBBox（cx, cy, w, h, angle）
     * @return 裁剪后的 ROI（若失败返回空 Mat）
     */
    static cv::Mat Crop(const cv::Mat& src, const OBBBox& box);

private:
    static cv::Mat RotateImage(
        const cv::Mat& src,
        const cv::Point2f& center,
        float angleRad);
};

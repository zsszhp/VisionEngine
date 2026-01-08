#include "pch.h"
#include "OBBCropper.h"
#include <cmath>

// ===============================
// 主入口：OBB 裁剪
// ===============================
cv::Mat OBBCropper::Crop(const cv::Mat& src, const OBBBox& box)
{
    if (src.empty())
        return cv::Mat();

    // 1️⃣ 旋转中心
    cv::Point2f center(box.cx, box.cy);

    // 2️⃣ Python 里用的是 -angle（你前面代码就是这么干的）
    float angleDeg = -box.angle * 180.0f / static_cast<float>(CV_PI);

    // 3️⃣ 旋转整张图
    cv::Mat rotated = RotateImage(src, center, angleDeg);
    if (rotated.empty())
        return cv::Mat();

    // 4️⃣ 裁剪尺寸（⚠️ 等价你 Python 的 h + 200）
    int cropW = static_cast<int>(box.w);
    int cropH = static_cast<int>(box.h + 200);

    if (cropW <= 0 || cropH <= 0)
        return cv::Mat();

    // 5️⃣ 从旋转后的图中裁 ROI（等价 getRectSubPix）
    cv::Mat roi;
    cv::getRectSubPix(
        rotated,
        cv::Size(cropW, cropH),
        center,
        roi
    );

    return roi;
}

// ===============================
// 旋转图像（等价 cv2.getRotationMatrix2D + warpAffine）
// ===============================
cv::Mat OBBCropper::RotateImage(
    const cv::Mat& src,
    const cv::Point2f& center,
    float angleDeg)
{
    // 1️⃣ 旋转矩阵
    cv::Mat rotMat = cv::getRotationMatrix2D(
        center,
        angleDeg,
        1.0);

    // 2️⃣ 输出图像
    cv::Mat dst;
    cv::warpAffine(
        src,
        dst,
        rotMat,
        src.size(),
        cv::INTER_LINEAR,
        cv::BORDER_REPLICATE);

    return dst;
}

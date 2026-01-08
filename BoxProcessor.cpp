#include "pch.h"
#include "BoxProcessor.h"
#include <algorithm>
#include <cmath>
#include <opencv2/opencv.hpp>

// ===============================
// sort_boxes_by_center
// Python:
// return sorted(boxes, key=lambda box: box[0])
// ===============================
void BoxProcessor::SortByCenterX(std::vector<OBBBox>& boxes)
{
    std::sort(boxes.begin(), boxes.end(),
        [](const OBBBox& a, const OBBBox& b)
        {
            return a.cx < b.cx;
        });
}

// ===============================
// remove_specific_boxes
// Python 逻辑完整等价
// ===============================
void BoxProcessor::RemoveSpecificBoxes(std::vector<OBBBox>& boxes, float imgHeight)
{
    // 找到需要删除的“参考 box”
    std::vector<OBBBox> boxesToRemove;

    for (const auto& box : boxes)
    {
        if (box.cy < imgHeight)
        {
            boxesToRemove.push_back(box);
        }
    }

    // 删除规则：
    // 1. 删除自身 cls == 0 且中心一致的 box
    // 2. 删除位于该 box 内部的 cls == 1 / 3
    for (const auto& refBox : boxesToRemove)
    {
        boxes.erase(
            std::remove_if(boxes.begin(), boxes.end(),
                [&](const OBBBox& box)
                {
                    // 条件 1
                    if (box.cls == 0 &&
                        box.cx == refBox.cx &&
                        box.cy == refBox.cy)
                        return true;

                    // 条件 2
                    if ((box.cls == 1 || box.cls == 3) &&
                        IsPointInRect(box.cx, box.cy, refBox))
                        return true;

                    return false;
                }),
            boxes.end());
    }
}

// ===============================
// is_point_in_rect
// Python 等价：cv2.boxPoints + pointPolygonTest
// ===============================
bool BoxProcessor::IsPointInRect(float px, float py, const OBBBox& rect)
{
    float points[4][2];
    GetBoxPoints(rect, points);

    std::vector<cv::Point2f> contour;
    for (int i = 0; i < 4; ++i)
    {
        contour.emplace_back(points[i][0], points[i][1]);
    }

    double res = cv::pointPolygonTest(
        contour,
        cv::Point2f(px, py),
        false);

    return res >= 0;
}

// ===============================
// 生成 OBB 四个角点（核心数学）
// 等价 Python：cv2.boxPoints
// ===============================
void BoxProcessor::GetBoxPoints(const OBBBox& box, float points[4][2])
{
    float cx = box.cx;
    float cy = box.cy;
    float w = box.w;
    float h = box.h;

    // Python 中使用的是 -r
    float angle = -box.angle;

    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    float hw = w * 0.5f;
    float hh = (h + 200) * 0.5f;  // ⚠️ 完整等价你 Python 里的 h+200

    // 四个角（未旋转）
    float local[4][2] =
    {
        {-hw, -hh},
        { hw, -hh},
        { hw,  hh},
        {-hw,  hh}
    };

    // 旋转 + 平移
    for (int i = 0; i < 4; ++i)
    {
        points[i][0] = cx + local[i][0] * cosA - local[i][1] * sinA;
        points[i][1] = cy + local[i][0] * sinA + local[i][1] * cosA;
    }
}

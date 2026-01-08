#pragma once
#include <vector>
#include "VisionTypes.h"

/**
 * @brief OBB 几何处理模块（等价 Python 逻辑）
 */
class BoxProcessor
{
public:
    // 按中心点 X 坐标排序（sort_boxes_by_center）
    static void SortByCenterX(std::vector<OBBBox>& boxes);

    // 删除特定 box（remove_specific_boxes）
    static void RemoveSpecificBoxes(std::vector<OBBBox>& boxes, float imgHeight);

    // 点是否在旋转矩形内（is_point_in_rect）
    static bool IsPointInRect(float px, float py, const OBBBox& rect);

private:
    // 内部工具：生成 OBB 的 4 个角点
    static void GetBoxPoints(const OBBBox& box, float points[4][2]);
};

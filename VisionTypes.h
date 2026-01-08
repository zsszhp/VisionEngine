#pragma once

#define MAX_BARCODE_COUNT 32
#define MAX_BARCODE_LENGTH 64

// 单个 OBB 框（等价 Python: [cx, cy, w, h, angle, conf, cls]）
struct OBBBox
{
    float cx;
    float cy;
    float w;
    float h;
    float angle;   // 弧度
    float conf;
    int   cls;
};

// YOLO 推理输出（一张图）
#define MAX_OBB_COUNT 256

struct YoloResult
{
    int box_count;
    OBBBox boxes[MAX_OBB_COUNT];
};

// 给 C# 的最终结果（上一批用的）
struct VisionResult
{
    int ok_ng;
    int ng_count;
    int fill_count;
    int barcode_count;
    char barcodes[MAX_BARCODE_COUNT][MAX_BARCODE_LENGTH];
};

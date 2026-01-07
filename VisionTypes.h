#pragma once

// 最大条码数量（根据你现在业务，先保守给 32）
#define MAX_BARCODE_COUNT 32

// 每个条码最大长度
#define MAX_BARCODE_LENGTH 64

// 算法返回结果结构体（给 C# 用）
struct VisionResult
{
    // 是否 OK：1 = OK，0 = NG
    int ok_ng;

    // NG 数量
    int ng_count;

    // 填充数量（FILL_COUNT）
    int fill_count;

    // 实际识别到的条码数量
    int barcode_count;

    // 条码字符串数组
    // barcodes[i] 是第 i 个条码
    char barcodes[MAX_BARCODE_COUNT][MAX_BARCODE_LENGTH];
};

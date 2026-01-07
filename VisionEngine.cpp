#include "pch.h"
#include "VisionEngine.h"
#include <cstring>   // for strcpy_s

int Vision_Run(const char* imagePath, VisionResult* result)
{
    if (imagePath == nullptr || result == nullptr)
    {
        return -1; // 参数错误
    }

    // 清空结构体（防止脏数据）
    memset(result, 0, sizeof(VisionResult));

    // ====== 下面是假数据（后面全部替换成真实算法） ======

    result->ok_ng = 1;
    result->ng_count = 0;
    result->fill_count = 3;

    result->barcode_count = 2;

    strcpy_s(result->barcodes[0], "CND123456");
    strcpy_s(result->barcodes[1], "BCS987654");

    return 0; // 成功
}

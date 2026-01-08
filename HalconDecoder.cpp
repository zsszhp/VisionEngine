#include "pch.h"
#include "HalconDecoder.h"
#include <halconcpp.h>
#include <cstring>

using namespace HalconCpp;

bool HalconDecoder::Decode(const cv::Mat& roi, VisionResult& result)
{
    // 初始化结果
    result.success = 0;
    result.confidence = 0.0f;
    std::memset(result.code, 0, sizeof(result.code));

    if (roi.empty())
        return false;

    try
    {
        // 1️⃣ OpenCV Mat → Halcon HObject
        HObject hImage;
        GenImageInterleaved(
            &hImage,
            roi.data,
            "bgr",
            roi.cols,
            roi.rows,
            -1,
            "byte",
            roi.step,
            0,
            0,
            8,
            0);

        // 2️⃣ 创建条码模型
        HTuple barcodeHandle;
        CreateBarCodeModel({}, {}, &barcodeHandle);

        // 常见工业条码（你可按需裁剪）
        SetBarCodeParam(barcodeHandle, "barcode_type",
            HTuple("QR Code").Append("Code 128").Append("Data Matrix"));

        // 3️⃣ 查找条码
        HObject regions;
        HTuple decodedStrings;
        FindBarCode(
            hImage,
            &regions,
            barcodeHandle,
            "auto",
            &decodedStrings);

        if (decodedStrings.Length() > 0)
        {
            std::string code = decodedStrings[0].S();

            std::strncpy(
                result.code,
                code.c_str(),
                sizeof(result.code) - 1);

            result.success = 1;
            result.confidence = 1.0f;
            ClearBarCodeModel(barcodeHandle);
            return true;
        }

        ClearBarCodeModel(barcodeHandle);
    }
    catch (...)
    {
        return false;
    }

    return false;
}

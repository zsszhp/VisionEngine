# D:\VisionEngine\models\export_onnx.py
import torch
from ultralytics import YOLO

# 加载训练好的模型
model = YOLO('best.pt')  # 替换为你的实际模型路径

# 导出为 ONNX 格式（必须指定 opset=12）
model.export(
    format='onnx',
    dynamic=True,           # 支持动态输入尺寸
    simplify=True,          # 简化 ONNX 图
    opset=12,               # 必须是 12+（YOLOv8 需要）
    imgsz=[640, 640]        # 与训练时一致
)

print("✅ ONNX 模型已导出到: D:\\VisionEngine\\models\\best.onnx")
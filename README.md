# VisionEngine 工业视觉引擎 - 完整文档

<p align="center">
  <b>企业级工业视觉引擎 (C# + C++ DLL)</b><br/>
  <i>YOLOv8 OBB · OpenCV · Halcon · 条码解码</i>
</p>

<p align="center">
  <a href="#英文版">English</a> | 
  <a href="#中文版">中文</a>
</p>

---

## 中文版

### 📌 项目介绍

**VisionEngine** 是一款专为工业应用设计的工业视觉算法引擎，采用 **C# + C++ DLL** 架构。核心算法全部基于 **原生C++** 实现，专注于：

* 工业图像处理
* YOLOv8 OBB (定向边界框检测)
* 几何逻辑与稳定裁剪
* Halcon条码/二维码解码
* 企业级DLL API封装

项目目标是：

> **取代C#调用Python EXE + 文件传输的低效方案，构建高性能、易维护、可交付的工业视觉核心引擎。**

---

### ✨ 核心特性

* ✅ **纯C++核心算法** (无Python运行时依赖)
* ✅ **YOLOv8 OBB旋转对象支持**
* ✅ **稳定的OBB几何滤波和裁剪逻辑**
* ✅ **OpenCV + Halcon工业级组合**
* ✅ **C风格DLL接口，C#直接P/Invoke调用**
* ✅ **零文件传输，内存级数据流**
* ✅ **内置日志系统，便于工程问题定位**

---

### 🏗️ 系统架构

```
C# 上位机
   ↓ (P/Invoke)
VisionEngine.dll (C++)
   ├─ YOLOv8 OBB推理 (ONNX)
   ├─ OBB几何逻辑处理
   ├─ OBB裁剪 + 旋转校正
   ├─ Halcon条码解码
   └─ 日志系统
```

---

### 📂 项目结构

```
VisionEngine/
├── include/            # 头文件
│   ├── VisionAPI.h
│   ├── VisionTypes.h
│   ├── VisionResult.h
│   ├── BoxProcessor.h
│   ├── OBBCropper.h
│   ├── HalconDecoder.h
│   └── Logger.h
│
├── src/                # 源文件
│   ├── VisionAPI.cpp
│   ├── BoxProcessor.cpp
│   ├── OBBCropper.cpp
│   ├── HalconDecoder.cpp
│   └── Logger.cpp
│
├── models/             # YOLOv8 ONNX模型
├── third_party/        # 第三方依赖 (如OpenCV)
├── docs/               # 文档
├── tests/              # 单元测试
├── cmake/              # CMake模块
├── examples/           # 示例代码
├── .github/            # GitHub配置
│   └── ISSUE_TEMPLATE/
├── .gitignore
├── README.md
├── README_en.md
├── LICENSE
├── CONTRIBUTING.md
└── CMakeLists.txt
```

---

### 🚀 快速开始

#### 系统要求
* Windows 10 / 11 (x64)
* Visual Studio 2022
* OpenCV 4.x (x64)
* Halcon 20+ (x64) - 需要商业许可
* .NET Framework / .NET 6+

#### 构建说明
```bash
# 克隆仓库
git clone <repository-url>
cd VisionEngine

# 创建构建目录
mkdir build
cd build

# 使用CMake配置
cmake .. -DCMAKE_BUILD_TYPE=Release

# 构建
cmake --build . --config Release
```

#### C# 使用示例
```csharp
// 初始化引擎
Vision_Init("vision.log");

// 处理图像
VisionResult result = new VisionResult();
int ret = Vision_ProcessImage("test.jpg", ref result);

if (ret == 0 && result.success == 1)
{
    Console.WriteLine($"检测结果: {result.code}");
}
else
{
    Console.WriteLine($"处理失败，错误代码: {ret}");
}

// 清理资源
Vision_Cleanup();
```

#### C++ 使用示例
```cpp
#include "VisionAPI.h"

int main() {
    Vision_Init("log.txt");
    
    VisionResult result;
    int ret = Vision_ProcessImage("input.jpg", &result);
    
    if (ret == 0 && result.success == 1) {
        // 处理结果
        std::cout << "结果: " << result.code << std::endl;
    }
    
    Vision_Cleanup();
    return 0;
}
```

---

### 🧪 运行环境

#### Windows
* Windows 10 / 11 (x64)
* Visual Studio 2022
* OpenCV 4.x (x64)
* Halcon 20+ (x64) - 需要商业许可
* .NET Framework / .NET 6+

#### 依赖项
* OpenCV 4.x - 计算机视觉库
* Halcon - 机器视觉库 (商业)
* ONNX Runtime - 模型推理
* CMake 3.15+ - 构建系统

---

### 📄 日志系统

项目内置轻量级日志模块，自动输出：

* 初始化状态
* 图像处理工作流
* 错误信息

示例：
```
[2026-01-08 21:30:13] [INFO] 正在处理图像: test.jpg
[2026-01-08 21:30:13] [INFO] 条码解码成功
[2026-01-08 21:30:14] [DEBUG] OBB检测完成，找到5个对象
[2026-01-08 21:30:15] [ERROR] 模型文件未找到: models/yolov8.onnx
```

---

### 🛠️ API 参考

#### 核心函数
* `Vision_Init(const char* log_path)` - 初始化引擎
* `Vision_ProcessImage(const char* image_path, VisionResult* result)` - 处理图像
* `Vision_ProcessImageData(const unsigned char* data, int width, int height, int channels, VisionResult* result)` - 处理图像数据
* `Vision_Cleanup()` - 清理资源
* `Vision_SetParameter(const char* key, double value)` - 设置参数

#### 返回码
* `0` - 成功
* `-1` - 参数无效
* `-2` - 文件未找到
* `-3` - 模型加载失败
* `-4` - 推理错误
* `-5` - 内存分配失败

---

### 🤝 贡献指南

欢迎各种形式的贡献！请查看 [CONTRIBUTING.md](CONTRIBUTING.md) 了解如何开始。

#### 开发设置
1. Fork 仓库
2. 创建功能分支: `git checkout -b feature/amazing-feature`
3. 进行修改
4. 提交更改: `git commit -m '添加某些 amazing 功能'`
5. 推送到分支: `git push origin feature/amazing-feature`
6. 创建 Pull Request

#### 代码风格
* 遵循 Google C++ 代码风格指南
* 使用有意义的变量和函数名称
* 添加适当的注释和文档
* 为新功能编写单元测试

---

### 🧪 测试

#### 单元测试
```bash
# 运行所有测试
./build/tests/vision_tests

# 运行特定测试套件
./build/tests/vision_tests --gtest_filter=VisionAPITest.*
```

#### CI/CD 流水线
* Windows/Linux 自动构建
* 单元测试执行
* 代码覆盖率分析
* 安全漏洞扫描

---

### 📈 性能

#### 基准测试
* YOLOv8 OBB推理: <50ms 每图像 (RTX 3080)
* 条码解码: <10ms 每图像
* OBB几何处理: <5ms 每操作

#### 优化特性
* GPU加速支持
* 多线程处理
* 内存池
* 零拷贝数据传输

---

### 🎯 设计理念

* **工程优先**: 优先考虑稳定性和可维护性
* **清晰接口**: C++仅暴露必要的API
* **性能导向**: 避免不必要的I/O和进程间通信
* **企业交付**: 满足实际工业项目需求
* **开源友好**: 遵循开源最佳实践

---

### 🐛 问题报告

如果遇到任何问题，请在 [Issues](https://github.com/username/VisionEngine/issues) 部分报告，包含：

1. 问题的清晰描述
2. 复现步骤
3. 期望行为
4. 实际行为
5. 环境信息 (操作系统、编译器等)
6. 相关日志或错误消息

---

### 📜 许可证

此项目基于 **MIT 许可证** - 查看 [LICENSE](LICENSE) 文件了解详情。

MIT 许可证允许免费使用、修改、分发和商业使用此软件。

---

### 🙏 致谢

* YOLOv8 提供最先进的目标检测
* OpenCV 提供计算机视觉算法
* Halcon 提供工业视觉能力
* ONNX Runtime 提供高效的模型推理

---

### 📞 支持

如需支持，请在 GitHub 仓库中提交 issue 或联系维护者。

* **文档**: [docs/](docs/)
* **示例**: [examples/](examples/)
* **问题跟踪**: [Issues](https://github.com/username/VisionEngine/issues)

---

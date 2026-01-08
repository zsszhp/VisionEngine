# VisionEngine Industrial Vision Engine
<p align="center">
  <b>Enterprise-level Industrial Vision Engine (C# + C++ DLL)</b><br/>
  <i>YOLOv8 OBB · OpenCV · Halcon · Barcode Decoding</i>
</p>

<p align="center">
  <a href="#english-version">English</a> | 
  <a href="#中文版本">中文</a>
</p>

---


### 📌 Project Introduction

**VisionEngine** is an industrial vision algorithm engine designed for industrial applications, adopting a **C# + C++ DLL** architecture. Core algorithms are all implemented in **native C++**, focusing on:

* Industrial image processing
* YOLOv8 OBB (Oriented Bounding Box detection)
* Geometric logic and stable cropping
* Halcon barcode/QR code decoding
* Enterprise-level DLL API encapsulation

The goal of this project is:

> **Replace the inefficient solution of C# calling Python EXE + file transfer, and build a high-performance, maintainable, and deliverable industrial vision core engine.**

---

### ✨ Core Features

* ✅ **Pure C++ core algorithms** (no Python runtime dependencies)
* ✅ **YOLOv8 OBB rotated object support**
* ✅ **Stable OBB geometric filtering and cropping logic**
* ✅ **OpenCV + Halcon industrial-grade combination**
* ✅ **C-style DLL interface, C# direct P/Invoke calls**
* ✅ **Zero file transfer, memory-level data flow**
* ✅ **Built-in logging system for easy engineering issue localization**

---

### 🏗️ System Architecture

```text
C# Upper Computer
   ↓ (P/Invoke)
VisionEngine.dll (C++)
   ├─ YOLOv8 OBB inference (ONNX)
   ├─ OBB geometric logic processing
   ├─ OBB cropping + rotation correction
   ├─ Halcon barcode decoding
   └─ Logging system
```

---

### 📂 Project Structure

```text
VisionEngine/
├── include/            # Header files
│   ├── VisionAPI.h
│   ├── VisionTypes.h
│   ├── VisionResult.h
│   ├── BoxProcessor.h
│   ├── OBBCropper.h
│   ├── HalconDecoder.h
│   └── Logger.h
│
├── src/                # Source files
│   ├── VisionAPI.cpp
│   ├── BoxProcessor.cpp
│   ├── OBBCropper.cpp
│   ├── HalconDecoder.cpp
│   └── Logger.cpp
│
├── models/             # YOLOv8 ONNX models
├── third_party/        # Third-party dependencies (e.g., OpenCV)
├── docs/               # Documentation
├── tests/              # Unit tests
├── cmake/              # CMake modules
├── examples/           # Example code
├── .github/            # GitHub configuration
│   └── ISSUE_TEMPLATE/
├── .gitignore
├── README.md
├── LICENSE
├── CONTRIBUTING.md
└── CMakeLists.txt
```

---

### 🚀 Quick Start

#### Prerequisites
* Windows 10 / 11 (x64)
* Visual Studio 2022
* OpenCV 4.x (x64)
* Halcon 20+ (x64) - Commercial License Required
* .NET Framework / .NET 6+

#### Build Instructions
```bash
# Clone repository
git clone <repository-url>
cd VisionEngine

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build . --config Release
```

#### C# Usage Example
```csharp
// Initialize engine
Vision_Init("vision.log");

// Process image
VisionResult result = new VisionResult();
int ret = Vision_ProcessImage("test.jpg", ref result);

if (ret == 0 && result.success == 1)
{
    Console.WriteLine($"Detection result: {result.code}");
}
else
{
    Console.WriteLine($"Processing failed with error code: {ret}");
}

// Cleanup resources
Vision_Cleanup();
```

#### C++ Usage Example
```cpp
#include "VisionAPI.h"

int main() {
    Vision_Init("log.txt");
    
    VisionResult result;
    int ret = Vision_ProcessImage("input.jpg", &result);
    
    if (ret == 0 && result.success == 1) {
        // Process results
        std::cout << "Result: " << result.code << std::endl;
    }
    
    Vision_Cleanup();
    return 0;
}
```

---

### 🧪 Runtime Environment

#### Windows
* Windows 10 / 11 (x64)
* Visual Studio 2022
* OpenCV 4.x (x64)
* Halcon 20+ (x64) - Commercial License Required
* .NET Framework / .NET 6+

#### Dependencies
* OpenCV 4.x - Computer vision library
* Halcon - Machine vision library (commercial)
* ONNX Runtime - Model inference
* CMake 3.15+ - Build system

---

### 📄 Logging System

The project has a built-in lightweight logging module that automatically outputs:

* Initialization status
* Image processing workflow
* Error information

Example:
```text
[2026-01-08 21:30:13] [INFO] Processing image: test.jpg
[2026-01-08 21:30:13] [INFO] Barcode decoded successfully.
[2026-01-08 21:30:14] [DEBUG] OBB detection completed, 5 objects found
[2026-01-08 21:30:15] [ERROR] Model file not found: models/yolov8.onnx
```

---

### 🛠️ API Reference

#### Core Functions
* `Vision_Init(const char* log_path)` - Initialize engine
* `Vision_ProcessImage(const char* image_path, VisionResult* result)` - Process image
* `Vision_ProcessImageData(const unsigned char* data, int width, int height, int channels, VisionResult* result)` - Process image data
* `Vision_Cleanup()` - Clean up resources
* `Vision_SetParameter(const char* key, double value)` - Set parameters

#### Return Codes
* `0` - Success
* `-1` - Invalid parameters
* `-2` - File not found
* `-3` - Model loading failed
* `-4` - Inference error
* `-5` - Memory allocation failed

---

### 🤝 Contributing

We welcome contributions of all kinds! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for how to get started.

#### Development Setup
1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Make your changes
4. Commit your changes: `git commit -m 'Add some amazing feature'`
5. Push to the branch: `git push origin feature/amazing-feature`
6. Open a Pull Request

#### Code Style
* Follow Google C++ Style Guide
* Use meaningful variable and function names
* Add appropriate comments and documentation
* Write unit tests for new features

---

### 🧪 Testing

#### Unit Tests
```bash
# Run all tests
./build/tests/vision_tests

# Run specific test suite
./build/tests/vision_tests --gtest_filter=VisionAPITest.*
```

#### CI/CD Pipeline
* Automated builds on Windows/Linux
* Unit test execution
* Code coverage analysis
* Security vulnerability scanning

---

### 📈 Performance

#### Benchmarks
* YOLOv8 OBB inference: <50ms per image (RTX 3080)
* Barcode decoding: <10ms per image
* OBB geometric processing: <5ms per operation

#### Optimization Features
* GPU acceleration support
* Multi-threaded processing
* Memory pooling
* Zero-copy data transfer

---

### 🎯 Design Philosophy

* **Engineering first**: Prioritize stability and maintainability
* **Clear interfaces**: C++ exposes only necessary APIs
* **Performance oriented**: Avoid unnecessary I/O and inter-process communication
* **Enterprise deliverable**: Meets real industrial project requirements
* **Open source friendly**: Follows open source best practices

---

### 🐛 Issue Reporting

If you encounter any issues, please report them in the [Issues](https://github.com/username/VisionEngine/issues) section with:

1. Clear description of the problem
2. Steps to reproduce
3. Expected behavior
4. Actual behavior
5. Environment information (OS, compiler, etc.)
6. Relevant logs or error messages

---

### 📜 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

The MIT License allows for free use, modification, distribution, and commercial use of this software.

---

### 🙏 Acknowledgments

* YOLOv8 for state-of-the-art object detection
* OpenCV for computer vision algorithms
* Halcon for industrial vision capabilities
* ONNX Runtime for efficient model inference

---

### 📞 Support

For support, please open an issue in the GitHub repository or contact the maintainers.

* **Documentation**: [docs/](docs/)
* **Examples**: [examples/](examples/)
* **Issue Tracker**: [Issues](https://github.com/username/VisionEngine/issues)

---

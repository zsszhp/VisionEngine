cmake_minimum_required(VERSION 3.10)
project(VisionEngine)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Halcon路径
set(HALCON_DIR "C:/Users/zzz/AppData/Local/Programs/MVTec/HALCON-23.11-Progress")
set(HALCON_INCLUDE_DIR "${HALCON_DIR}/include")
set(HALCON_LIB_DIR "${HALCON_DIR}/lib/x64-win64")

# 设置ONNX Runtime路径
set(ONNXRUNTIME_DIR "C:/A/onnxruntime-win-x64-gpu-1.22.0")
set(ONNXRUNTIME_INCLUDE_DIR "${ONNXRUNTIME_DIR}/include")
set(ONNXRUNTIME_LIB_DIR "${ONNXRUNTIME_DIR}/lib")

# 设置OpenCV路径
set(OpenCV_DIR "C:/A/opencv/build")
find_package(OpenCV REQUIRED)

# 添加头文件目录
include_directories(
    ${HALCON_INCLUDE_DIR}
    ${ONNXRUNTIME_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

# 添加源文件
add_library(VisionEngine SHARED
    src/VisionEngine.cpp
    src/YOLOModel.cpp
    src/HalconWrapper.cpp
)

# 添加库文件
target_link_libraries(VisionEngine
    ${HALCON_LIB_DIR}/HalconCpp.lib
    ${ONNXRUNTIME_LIB_DIR}/onnxruntime.lib
    ${OpenCV_LIBS}
)

# 设置DLL导出
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties(VisionEngine PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)
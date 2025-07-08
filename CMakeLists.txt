# 指定项目所需的 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(c_calcu)

# 设置构建类型为 Debug，开启调试功能
set(CMAKE_BUILD_TYPE Debug)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 在 Debug 模式下添加调试信息
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 查找源文件
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})    
cmake_minimum_required(VERSION 3.29)
project(edge_framework)

# 指定C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 将第三方库的头文件路径添加到全局包含路径
include_directories(
        third_party
        include
)
# 源文件目录
set(SRCDIR src)

# 收集所有 .cpp 文件
file(GLOB SOURCES "${SRCDIR}/*.cpp")

add_executable(edge_framework
    main.cpp
)

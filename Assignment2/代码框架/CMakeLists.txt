cmake_minimum_required(VERSION 3.25.2)
project(Rasterizer)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include")
include_directories("/usr/local/Cellar/opencv/4.6.0/include/opencv4")
# include_directories("/usr/local/Cellar/eigen/3.4.0_1/include")

add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp)
target_link_libraries(Rasterizer ${OpenCV_LIBRARIES})

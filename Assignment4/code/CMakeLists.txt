cmake_minimum_required(VERSION 3.25.2)
project(BezierCurve)


find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/local/include")
include_directories("/usr/local/Cellar/opencv/4.6.0/include/opencv4")

add_executable(BezierCurve main.cpp)

target_link_libraries(BezierCurve ${OpenCV_LIBRARIES})

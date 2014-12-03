cmake_minimum_required (VERSION 2.8)
project (CoinCounter)

option (MAKE_TESTS 
        "Compile tests for computer vision code" ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory (src)
add_subdirectory (test)

find_package(OpenCV REQUIRED)
add_executable(ImgDisplay imgDisplay.cpp)
target_link_libraries(ImgDisplay ${OpenCV_LIBS})

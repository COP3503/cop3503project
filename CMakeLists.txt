cmake_minimum_required (VERSION 2.8)
project (CoinCounter)

option (MAKE_TESTS 
        "Compile tests for computer vision code" ON) 


# set (PROJECT_SOURCE_DIR src)
# set (PROJECT_BINARY_DIR bin)
# set (Tutorial_VERSION_MAJOR 0)
# set (Tutorial_VERSION_MINOR 1)
#
# configure_file(
#   "${PROJECT_SOURCE_DIR}/main.h.in"
#   "${PROJECT_BINARY_DIR}/main.h"
# )

add_subdirectory (src)
add_subdirectory (test)

find_package(OpenCV REQUIRED)
add_executable(ImgDisplay imgDisplay.cpp)
target_link_libraries(ImgDisplay ${OpenCV_LIBS})
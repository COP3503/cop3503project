cmake_minimum_required (VERSION 2.8)
project (CoinCounter)

# set (PROJECT_SOURCE_DIR src)
# set (PROJECT_BINARY_DIR bin)
# set (Tutorial_VERSION_MAJOR 0)
# set (Tutorial_VERSION_MINOR 1)
#
# configure_file(
#   "${PROJECT_SOURCE_DIR}/main.h.in"
#   "${PROJECT_BINARY_DIR}/main.h"
# )

#include_directories("${PROJECT_BINARY_DIR}")

find_package(OpenCV REQUIRED)
add_executable(ImgDisplay imgDisplay.cpp)
target_link_libraries(ImgDisplay ${OpenCV_LIBS})

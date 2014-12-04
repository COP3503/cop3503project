cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

add_subdirectory (vision)

add_executable (mainTest
    mainTest.cpp
    Data.cpp
    coin.cpp
    ${PROJECT_SOURCE_DIR}/test/coins_1.jpg
)
    target_link_libraries(mainTest ${OpenCV_Libs} ${OpenCV_LIBRARIES})

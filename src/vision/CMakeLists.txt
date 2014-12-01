cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )
set(the_description "Vision tools for the coin counting application.")

add_library ( COP3503_VISION SHARED ${PROJECT_SOURCE_DIR}/binarize.cpp )

#if(MAKE_TESTS)

    add_executable (vision_test
    	coin.cpp
        vision_test.cpp
        binarize.cpp
#        ${PROJECT_SOURCE_DIR}/test/coins_1.jpg
    )
    target_link_libraries(vision_test ${OpenCV_Libs} ${OpenCV_LIBRARIES})

#ENDIF(MAKE_TESTS)  # Or something like that


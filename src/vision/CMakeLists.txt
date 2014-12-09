cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

option(WITH_GTK "Enable GTK Version" On)

set(the_description "Vision tools for the coin counting application.")

#add_library ( COP3503_VISION SHARED ${PROJECT_SOURCE_DIR}/binarize.cpp ))

<<<<<<< HEAD
if(MAKE_TESTS)

    add_executable (vision_test
        vision_test.cpp
        binarize.cpp
        label.cpp
        visualization.cpp
    )
    target_link_libraries(vision_test ${OpenCV_Libs} ${OpenCV_LIBRARIES} ${libgtk2.0-dev_LIBRARIES})

ENDIF(MAKE_TESTS)  # Or something like that
=======
#if(MAKE_TESTS)
#
#    add_executable (vision_test
#        vision_test.cpp
#        binarize.cpp
#        label.cpp
#        visualization.cpp
#        ${PROJECT_SOURCE_DIR}/test/coins_1.jpg
#    )
#    target_link_libraries(vision_test ${OpenCV_Libs} ${OpenCV_LIBRARIES} ${libgtk2.0-dev_LIBRARIES})

#ENDIF(MAKE_TESTS)  # Or something lixke that
>>>>>>> forSubmission




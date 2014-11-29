COP3503 Project
===============

This is the COP3503 project for our group. The goal is to detect and count coins in an image.

[Find it here](https://github.com/COP3503/cop3503project)

# Usage

To build the project, make a directory in the repository's root folder called "build" (This would look like blabla/jacob/cop3503project/build), then

    cd ./build
    cmake ..
    make 

Then run whichever file you like. Please do not commit your build folder.

To run the vision tests, cd into build/src/vision and type ./vision_test

# Using Cmake

When you create a new folder, add it in the root CMakeLists.txt, doing add_subdirectory(FOLDER NAME). Then create a CMakelists.txt file in that folder. Please look at the other folders for examples of how to do this.


# Members
	* Brett Nelson
	* Ryan Nordman
	* Mani Angerhofer
	* Sahar Kausar
	* Jacob Panikulam
	* Ming Yang

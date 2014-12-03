#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "binarize.h"
#include "label.cpp"

/* 
    This file contains unit tests for the vision code
*/

// Use this main as an example

using namespace cv;

int main(int argc, char* argv[]) {
  Mat input_image;
  input_image = imread("../../test/coins_1.jpg", CV_LOAD_IMAGE_COLOR);

  // Again, should be using smart ptrs
  // get_hsv_masks(input_image);
  // imshow("Test Image", input_image);  

  vector<Mat*> masks = get_hough_masks(input_image);
  std::cout << masks.size() << std::endl;
  for (size_t j = 0; j < masks.size(); j++) {
    imshow("One element of the mask vector", *masks[j]);
    // imwrite("my image file.png", *masks[j]);
    waitKey(0);
  }
  waitKey(0);
  
   std::map<std::string, double> sampleDiamResults = {
        {"penny", 0.90}, {"nickel", 0.3}, {"dime", 0.98}, {"quarter", 0.2}
    };
   std::map<std::string, double> sampleColorResults = {
        {"penny", 0.1}, {"nickel", 0.3}, {"dime", 0.3}, {"quarter", 0.3}
    };
   std::vector< std::map<std::string, double> > sampleInput = {
       {sampleDiamResults}, {sampleColorResults}
   };
   
   std::cout << "Test Result: " << label(sampleInput) << std::endl;
   
  return 0;
}

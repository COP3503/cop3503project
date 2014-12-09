#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "vision.h"
#include <math.h>

/* 
    This file contains unit tests for the vision code
*/

// Use this main as an example


using namespace cv;
using namespace std;




int main(int argc, char* argv[]) {
  int i; 
  Mat input_image = imread("../../test/Real_test_imgs/img6.JPG", CV_LOAD_IMAGE_COLOR);
  vector<Mat> hsv_masks = get_hsv_masks(input_image);
  
    for(i = 0; i < hsv_masks.size(); i++){
    imshow( "Contours", hsv_masks[i] );
  waitKey(500);
 }

/*
  Again, should be using smart ptrs
  get_hsv_masks(input_image);
  imshow("Test Image", input_image);  

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
   */
  return 0;
}
/*
std::string identify_color_coin(Mat input_image, Mat mask) {

  input_image = imread("../../test/coins_1.jpg", CV_LOAD_IMAGE_COLOR);
  
  Mat color_mask;

  //AND the mask and the image together, store into color_mask
  bitwise_and(input_image, mask, color_mask);

  //color_mask now have one circle with color and everyting else is black
  //get hsv value


  //determine coin from values
}

*/


#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "binarize.h"

using namespace cv;

std::vector<Mat*> get_hough_masks(Mat input_image ) {
  /* Given an RGB input image, returns a vector of images 
    Example:
      vector<Mat*> masks = get_hough_masks(input_image);
      std::cout << masks.size() << std::endl;
      for (size_t j = 0; j < masks.size(); j++) {
        imshow("One element of the mask vector", *masks[j]);
        waitKey(0);
      }
  */
  std::vector<Mat*> masks;

  // Greyscaling of input image
  Mat input_gray;
  cvtColor(input_image, input_gray, CV_BGR2GRAY);
  std::vector<Vec3f> circles;
  GaussianBlur(input_gray, input_gray, Size(9, 9), 2, 2);
  HoughCircles(input_gray, circles, CV_HOUGH_GRADIENT, 1, input_gray.rows/8, 200, 100, 0, 0);

  for( size_t i = 0; i < circles.size(); i++ )
  {
    // Should be using smart pointers - will fix
    Mat * mask = new Mat(input_image.rows, input_image.cols, CV_8U, Scalar(0, 0, 0));

    // Get center of the coin
    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);  // Mani: This is the radius of the coin
    // Circle center
    circle(input_image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
    // Circle outline
    circle(input_image, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    // Draw circle mask onto image
    circle(*mask, center, radius, 255, -1, 8, 0);

    masks.push_back(mask);
  }
  return masks;
}

void get_hsv_masks(Mat input_image) {
  Mat input_image_HSV;
  cvtColor(input_image, input_image_HSV, CV_BGR2HSV);
  // adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)

  Mat channel[3];
  split(input_image_HSV, channel);
  
  Mat thresh_H, thresh_S, thresh_V;
  // ADAPTIVE_THRESH_MEAN_C
  adaptiveThreshold(channel[0], thresh_H,  10.0, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 1);
  adaptiveThreshold(channel[1], thresh_S,  10.0, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 1);
  adaptiveThreshold(channel[2], thresh_V,  10.0, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 1);


  imshow("thresh_H", thresh_H );
  imshow("thresh_S", thresh_S );
  imshow("thresh_V", thresh_V );

  imshow("H", channel[0]);
  imshow("S", channel[1]);
  imshow("V", channel[2]);

  // Copper:
  // 5°, 39%, 68

  waitKey(0);
}



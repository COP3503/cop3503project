#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "vision.h"
#include <string.h>

using namespace cv;

#define cop_H_Low 2
#define cop_H_High 2
#define cop_S_Low 99
#define cop_S_High 99
#define cop_V_Low 173
#define cop_V_High 173

#define sil_H_Low 2
#define sil_H_High 2
#define sil_S_Low 99
#define sil_S_High 99
#define sil_V_Low 173
#define sil_V_High 173


std::vector<Mat*> get_hough_masks(Mat input_image) {
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
    // Draw a circle's center (This draws on the original image)
    // circle(input_image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
    // Draw a circle's outline (This draws on the original image)
    // circle(input_image, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    // Draw circle mask onto image
    circle(*mask, center, radius, 255, -1, 8, 0);

    masks.push_back(mask);
  }
  return masks;
}


void get_hsv_masks(Mat input_image) {
  Mat input_image_HSV, input_image_HSVmask_Copper, input_image_HSVmask_Silver;

  Mat hsv_mask;

  cvtColor(input_image, input_image_HSV, CV_BGR2HSV);
  // adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)

  //inrange for copper
  inRange(input_image_HSV, Scalar(cop_H_Low, cop_S_Low, cop_V_Low), Scalar(cop_H_High, cop_S_High, cop_V_High), input_image_HSVmask_Copper);

  //inragne for silver
  inRange(input_image_HSV, Scalar(sil_H_Low, sil_S_Low, sil_V_Low), Scalar(sil_H_High, sil_S_High, sil_V_High), input_image_HSVmask_Silver);

  //or all images together into one hsv mask
  bitwise_or(input_image_HSVmask_Silver, input_image_HSVmask_Copper, hsv_mask);





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

//somewhere is going to take the original image and and it with all the masks. return color name
std::string identify_color_coin(Mat input_image, Mat mask) {
  
  Mat color_mask;
  //AND the mask and the image together, store into color_mask
  bitwise_and(input_image, mask, color_mask);

  //color_mask now have one circle with color and everyting else is black
  //get hsv value


  //determine coin from values
}


#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "vision.h"
#include <string.h>

using namespace cv;
using namespace std;
RNG rng(12345); 

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

  /*

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
  */

  vector<Mat*> hsv_masks = get_hsv_masks(input_image);
  return hsv_masks;
}

//a used by get_hsv_masks(). it determine if a circle is a complete one
int not_full_circle(float radius, double area){
  int a, a_min;
  a = 3.14*radius*radius;
  a_min = a-(a*.4);
  if (area<a_min){
    return 1;
  }
  return 0;
}

vector<Mat*> get_hsv_masks(Mat input_image) {
  /*takes in a RGB image of coins and return a vector of pointers to masks extracted from using HSV values.
  the vector is not a binary image, but it can be anded with other images because the masked area is all
  black(false) and the part of the coin is white(true)
  
  EXAMPLE:
  *******************************
  Mat input_image = imread("../../test/Real_test_imgs/img6.JPG", CV_LOAD_IMAGE_COLOR);
  vector<Mat*> hsv_masks = get_hsv_masks(input_image);

  for(i = 0; i < hsv_masks.size(); i++){
    imshow( "Contours", hsv_masks[i] );
    waitKey(500);
  }
  *******************************
  this is going to individually show each mask, flashing at 0.5 sec rate.
  */

  // <- is comments
  ///////// <- is what we could use to show current state image

  int i;
  Mat input_image_HSV = Mat::zeros( input_image.size(), CV_8UC3 );

  //resize image if it's too big to fit screen
  if( (input_image.cols > 600)   &&  (input_image.rows > 350) ) {
    resize(input_image, input_image, Size(input_image.cols/8, input_image.rows/8)); // resized to half size
  }

  //convert to hsv
  cvtColor(input_image, input_image_HSV, CV_BGR2HSV);

  //split image into 3 channels
  Mat channel[3];
  split(input_image_HSV, channel);

  //take adaptiveThreshold of Channel V
  Mat thresh_H, thresh_S, thresh_V;
  adaptiveThreshold(channel[2], thresh_V,  255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 333, 0);
  /////////imshow("thresh_V before finding contours", thresh_V);

  //find thresh_V contours, storing all of the contours in "contours"
  vector<Vec4i> hierarchy;
  vector<vector<Point>> contours;
  findContours(thresh_V, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0,0));
  /////////imshow("thresh_V after finding thresh_V_contours", thresh_V);

  //create circles and radius
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );

  //get circles
  for( i = 0; i < contours.size(); i++ ){ 
      minEnclosingCircle( (Mat)contours[i], center[i], radius[i] );
  }

  // draw circile contours
  Mat thresh_V_contours = Mat::zeros( thresh_V.size(), CV_8UC3 );//create a new Mat for the 
  Scalar color = Scalar(255, 250, 250);
  for( i = 0; i< contours.size(); i++ ){
      drawContours( thresh_V_contours, contours, -1, color, 1, 8, vector<Vec4i>(), 0, Point() );
      circle( thresh_V_contours, center[i], (int)radius[i], color, 1, 8, 0 );
  }
  /////////imshow( "thresh_V_contours", thresh_V_contours );

  //approximate all the circles(to get rid of the ones that has very small areas, aka, sparse)
  vector<vector<Point> > approx( contours.size() );
  vector<double> area0;
  double area0_total;
  double area0_avg;

  //get rid of all the circles with area == 0 after aprpoximation
  for(i = 0; i< contours.size(); i++){
      approxPolyDP( Mat(contours[i]), approx[i], 2, true);
      if(contourArea(approx[i]) == 0){
        continue;
      }
       area0.push_back(contourArea(approx[i]));
  }

  //take average of all approx area first time
  for(i = 0; i < area0.size(); i++){
      /////////cout << "area1 =" << area0[i] << endl;
      area0_total += area0[i];
  }
  area0_avg =  area0_total/area0.size();

  //after taking the avg, calcualte the range number for anything less than 7% and take all of those numbers out
  vector<double> area1;
  double area0_min = area0_avg * .07;
  double area1_total;
  double area1_avg;

  //get rid of anything area less than 7% of the average
   for(i = 0; i< contours.size(); i++){
      if(contourArea(approx[i]) < area0_min){
        continue;
      }
       //area1 has all the areas without 0 and numbers<7%
       area1.push_back(contourArea(approx[i]));
  }
  //recalculate the average without the area less than 7%
  for(i = 0; i < area1.size(); i++){
      /////////cout << "area1 =" << area1[i] << endl;
      area1_total += area1[i];
  }
  area1_avg =  area1_total/area1.size();
  /////////cout << "area1 size "<< area1.size() << endl;
  /////////cout << "area1 avg "<< area1_avg << endl;


  //use area1(the approximated one) to calculate the min and max of the remaining cirles for further filtering
  double area_range_min = area1_avg/4;
  double area_range_max = area1_avg * 2;

  //remove all circles out of bound of min and max(by ceating a new image and getting all the images that falls within the range)
  Mat thresh_V_contours_polished = Mat::zeros( thresh_V.size(), CV_8UC3 );
  for( i = 0; i< approx.size(); i++ ){
      if( ( contourArea(approx[i]) > area_range_max ) || ( contourArea(approx[i]) < area_range_min ) ){
        continue;
      }
      if( not_full_circle( radius[i], contourArea(approx[i]) ) == 1 )  {
        continue;
      }
      drawContours( thresh_V_contours_polished, approx, -1, color, 1, 8, vector<Vec4i>(), 0, Point() );
      circle( thresh_V_contours_polished, center[i], (int)radius[i], color, CV_FILLED, 8, 0 );
  }
  /////////imshow( "thresh_V_contours_polished before", thresh_V_contours_polished );

  //convert image into grayscale and then binary for mask splitting.
  Mat grayscaleMat;
  cvtColor( thresh_V_contours_polished, grayscaleMat, CV_BGR2GRAY );
  Mat binaryMat;
  threshold(grayscaleMat, binaryMat, 0, 255, THRESH_BINARY);
  /////////imshow("binary image", binaryMat);


  //split masks by finding contours and and then putting them all into individual images

  //find contours again
  vector<vector<Point> > mask_contours;
  vector<Vec4i> hierarchy1;
  findContours(binaryMat, mask_contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  //split all the masks into mask_vector
  Scalar binary_color = Scalar(255);
  vector<Mat*> mask_vector;
  for( i = 0; i< mask_contours.size(); i++ ){
    Mat * temp = new Mat(input_image.rows, input_image.cols, CV_8U, Scalar(0));
       drawContours( *temp, 
                      mask_contours, i, binary_color, CV_FILLED, 8, hierarchy1, 0, Point() );
       mask_vector.push_back(temp);
  }
   
  ///////// for(i = 0; i < mask_vector.size(); i++){
  /////////    imshow( "Contours", mask_vector[i] );
  /////////    waitKey(500);
  ///////// }
  ///////// waitKey(0);

  return mask_vector;

}


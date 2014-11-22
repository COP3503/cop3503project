#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

vector<Mat*> get_hough_masks(Mat input_image ) {
  /* Given an RGB input image, returns a vector of images 
    
    Example:
      vector<Mat*> masks = get_hough_masks(input_image);
      std::cout << masks.size() << std::endl;
      for (size_t j = 0; j < masks.size(); j++) {
        imshow("One element of the mask vector", *masks[j]);
        waitKey(0);
      }

    
  */
  vector<Mat*> masks;

  // Greyscaling of input image
  Mat input_gray;
  cvtColor(input_image, input_gray, CV_BGR2GRAY);
  vector<Vec3f> circles;
  GaussianBlur(input_gray, input_gray, Size(9, 9), 2, 2);
  HoughCircles(input_gray, circles, CV_HOUGH_GRADIENT, 1, input_gray.rows/8, 200, 100, 0, 0);

  for( size_t i = 0; i < circles.size(); i++ )
  {
    // Should be using smart pointers - will fix
    Mat * mask = new Mat(input_image.rows, input_image.cols, CV_8U, Scalar(0, 0, 0));

    // Get center of the coin
    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
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
  imshow("HSV", input_image_HSV);
  waitKey(0);
}


// Use this main as an example

int main(int argc, char* argv[]) {
  Mat input_image;
  input_image = imread("/home/jacob/repos/cop3503/cop3503project/test/coins_1.jpg", CV_LOAD_IMAGE_COLOR);
  // Again, should be using smart ptrs
  get_hsv_masks(input_image);
  imshow("Test Image", input_image);  

  waitKey(0);

  return 0;
}

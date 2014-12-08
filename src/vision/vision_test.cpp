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


int erosion_size = 1;

int dilation_size = 3;

using namespace cv;
using namespace std;
RNG rng(12345); 


int main(int argc, char* argv[]) {
  int i;
  Mat input_image;
  Mat input_image_HSV, input_image_HSVmask_Copper, input_image_HSVmask_Silver, hsv_mask;
  std::vector<Mat*> hough_masks_vector;



   //read in images
  input_image = imread("../../test/Real_test_imgs/ming2.JPG", CV_LOAD_IMAGE_COLOR);
  
  //convert to hsv
  cvtColor(input_image, input_image_HSV, CV_BGR2HSV);
  
  //resize image
  resize(input_image_HSV, input_image_HSV, Size(input_image_HSV.cols/8, input_image_HSV.rows/8)); // resized to half size

  


  //mask the copper color_mask
  inRange(input_image_HSV, Scalar(0, 0, 0), Scalar(20, 255, 255),input_image_HSVmask_Copper);

  //mask the silver color
  inRange(input_image_HSV, Scalar(50, 0, 0), Scalar(100, 100, 255),input_image_HSVmask_Silver);

  //combine the two images together   
  bitwise_or(input_image_HSVmask_Silver, input_image_HSVmask_Copper, hsv_mask);
  
  //just working on copper and displaying that for now
/*  imshow("hsv_mask", hsv_mask);
    waitKey(0);*/




  Mat channel[3];
  vector<Vec4i> hierarchy;
  vector<vector<Point>> contours;

  split(input_image_HSV, channel);

  Mat thresh_H, thresh_S, thresh_V;
  // ADAPTIVE_THRESH_MEAN_C 

  adaptiveThreshold(channel[2], thresh_V,  255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 433, 0);
  //threshold( channel[2], thresh_V, 100, 255, THRESH_BINARY );
  
  imshow("thresh_V before finding contours", thresh_V);

  //find thresh_V contours, storing all of the contours in "contours"
  findContours(thresh_V, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

  //set up contours
  vector<vector<Point> > contours_approx( contours.size() );
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );

  //get circles
  for( i = 0; i < contours.size(); i++ ){ 
      //approxPolyDP( Mat(contours[i]), contours_approx[i], 0, false);
      minEnclosingCircle( (Mat)contours[i], center[i], radius[i] );
  }


  // draw circile contours, colorful ones!
  Mat thresh_V_contours = Mat::zeros( thresh_V.size(), CV_8UC3 );//create a new Mat for the 

  for( i = 0; i< contours.size(); i++ ){
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      drawContours( thresh_V_contours, contours, -1, color, 1, 8, vector<Vec4i>(), 0, Point() );
      circle( thresh_V_contours, center[i], (int)radius[i], color, 1, 8, 0 );
  }


  imshow("thresh_V after finding thresh_V_contours", thresh_V);
  imshow( "thresh_V_contours", thresh_V_contours );


  //find all areas of all the circles
 
  //approximate for area1? let's try this
  vector<vector<Point> > approx( contours.size() );

  vector<double> area0;
  double area0_total;
  double area0_avg;

  for(i = 0; i< contours.size(); i++){
      approxPolyDP( Mat(contours[i]), approx[i], 2, true);
      if(contourArea(approx[i]) == 0){
        continue;
      }
       area0.push_back(contourArea(approx[i]));
  }


  for(i = 0; i < area0.size(); i++){
      cout << "area1 =" << area0[i] << endl;
      area0_total += area0[i];
  }
  area0_avg =  area0_total/area0.size();

  //after taking the avg, calcualte the range number for anything less than 7% and take all of those numbers out
  vector<double> area1;
  double area0_min = area0_avg*.07;
  double area1_total;
  double area1_avg;


   for(i = 0; i< contours.size(); i++){
      if(contourArea(approx[i]) < area0_min){
        continue;
      }
       area1.push_back(contourArea(approx[i]));
  }
      //recalculate the average
  for(i = 0; i < area0.size(); i++){
      cout << "area1 =" << area1[i] << endl;
      area1_total += area1[i];
  }
  area1_avg =  area1_total/area1.size();


 cout << "area1 size "<< area1.size() << endl;

 cout << "area1 avg "<< area1_avg << endl;


//use area1(the approximated one) to calculate average

  double area_range_min;
  double area_range_max;


 area_range_max = area1_avg*2;
 area_range_min = area1_avg/4;

  //***************************take histogram of all the circle areas********************************
 /* 
  //find number of areas in both array
  int numbers_of_areas0 = sizeof(area0)/8;
  int numbers_of_areas1 = sizeof(area1)/8;


  //find the max and min in both arrays
  double area0_min=area0[0];
  double area0_max=area0[0];
  double area1_min=area1[0];
  double area1_max=area1[0];

  for(i=0; i<numbers_of_areas0; i++){
    if (area0_min > area0[i]){
      area0_min = area0[i];
    }
    if (area0_max < area0[i]){
      area0_max = area0[i];
    }
  }

  for(i=0; i<numbers_of_areas1; i++){
    if (area1_min > area1[i]){
      area1_min = area1[i];
    }
    if (area1_max < area1[i]){
      area1_max = area1[i];
    }
  }
  cout<<"area0 min"<< area0_min << endl;
  cout<<"area0 max"<< area0_max << endl;
  cout<<"area1 min"<< area1_min << endl;
  cout<<"area1 max"<< area1_max << endl;

  //just take away all the zero?

  //determine number of class intervals
  int interval_num0 = (int)(sqrt(numbers_of_areas0));
  int interval_num1 = (int)(sqrt(numbers_of_areas1));

  cout<<" interval_num0"<<  interval_num0 << endl;
  cout<<"interval_num1"<< interval_num1 << endl;
*/

  //***************************take histogram of all the circle areas********************************

  //remove all circles in the smallest and biggest ones(by ceating a new image and getting all the images that falls within the range)
  Mat thresh_V_contours_polished = Mat::zeros( thresh_V.size(), CV_8UC3 );//create a new Mat for the 

  for( i = 0; i< contours.size(); i++ ){
      Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
      
      if( (contourArea(approx[i]) > area_range_max) || (contourArea(approx[i]) < area_range_min) ){
        continue;
      }

      
      drawContours( thresh_V_contours_polished, approx, -1, color, 1, 8, vector<Vec4i>(), 0, Point() );
      circle( thresh_V_contours_polished, center[i], (int)radius[i], color, 1, 8, 0 );
  }
  imshow( "thresh_V_contours_polished", thresh_V_contours_polished );

  //fill in all circles

  

  //**************************dilation and erosion********************************
/*

  Mat element = getStructuringElement( MORPH_ELLIPSE,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  
  /// Apply the dilation operation
  dilate( thresh_V, thresh_V, element );

  imshow( "Dilation Demo", thresh_V);



  element = getStructuringElement( MORPH_ELLIPSE,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );


  // Apply the erosion operation
  erode( thresh_V, thresh_V, element );
  imshow( "Erosion Demo", thresh_V);
  //waitKey(0);*/
  //**************************dilation and erosion********************************

  







  /*imshow("H", channel[0]);
  imshow("S", channel[1]);
  imshow("V", channel[2]);*/

/*  imshow("thresh_H", thresh_H );
  imshow("thresh_S", thresh_S );*/
  //imshow("thresh_V", thresh_V );

 /* Mat ORresult;

  bitwise_or(thresh_V, hsv_mask, ORresult);
 
  imshow("OR", ORresult);
*/
  
  // Copper:
  // 5°, 39%, 68

  waitKey(0);


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
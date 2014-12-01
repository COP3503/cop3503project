#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "binarize.h"
#include "coin.h"

/* 
    This file contains unit tests for the vision code
*/

// Use this main as an example

using namespace cv;
using namespace std;

//Diameter compare
void compareCoins(Coin array[], int size){
  for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
      if(i != j){
	array[i].compare(array[j]);
      }
    }
  }

  for(int i = 0; i<size
; i++){
    array[i].bestProb();
    array[i].printProbs();
  }
}

int main(int argc, char* argv[]) {

  Mat img1 = imread("/home/mani/School/COP3503/Homework/Final/cop3503project/test/coins_1_mask_1.png");
  Mat img2 = imread("/home/mani/School/COP3503/Homework/Final/cop3503project/test/coins_1_mask_2.png");
  Mat img3 = imread("/home/mani/School/COP3503/Homework/Final/cop3503project/test/coins_1_mask_3.png");

  Coin coinArray[3]{{img1},{img2},{img3}};

  compareCoins(coinArray,3);

  for(int i = 0; i<3; i++){
    cout<<"Coin"<<i<<" Probs"<<endl; 
    cout<<"Penny% = "<<coinArray[i].finalProbabilities.at(0)<<endl;
    cout<<"Nickel% = "<<coinArray[i].finalProbabilities.at(1)<<endl;
    cout<<"Dime% = "<<coinArray[i].finalProbabilities.at(2)<<endl;
    cout<<"Quarter% = "<<coinArray[i].finalProbabilities.at(3)<<endl;
    cout<<endl;
  }

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
  return 0;
}

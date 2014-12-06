#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "Data.h"
//#include "coin.h"
//#include "vision/binarize.cpp"
//#include "vision/label.cpp"

using namespace cv;
#define cop_H_Low 2.5
#define cop_H_High 2.5
#define cop_S_Low 99
#define cop_S_High 99
#define cop_V_Low 173
#define cop_V_High 173

/*#define silver_H_Low
#define silver_H_High
#define silver_S_Low
#define silver_S_High
#define silver_V_Low
#define silver_V_High*/

int main(int argc, char* argv[]) {
/*
    std::string imgPath = "test/coins_1.jpg";
    imshow("input image", imread(imgPath));
    Data data = Data(imgPath);
*/
    Mat input_image = imread("../test/coins_1.jpg");
    Mat input_image_HSV, input_image_HSVmask_Copper, input_image_HSVmask_Silver;


    cvtColor(input_image, input_image_HSV, CV_BGR2HSV);
    // adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)

    //inrange for copper
    inRange(input_image_HSV, Scalar(cop_H_Low, cop_S_Low, cop_V_Low), Scalar(cop_H_High, cop_S_High, cop_V_High),input_image_HSVmask_Copper);

    //inragne for silver
    

    imshow("copper color mask", input_image_HSV);


    //    Mat img1 = imread("../test/coins_1_mask_1.png");
    //    Mat img2 = imread("../test/coins_1_mask_2.png");
    //    Mat img3 = imread("../test/coins_1_mask_3.png");
    //    
    //    Coin coin1 = Coin(img1);
    //    Coin coin2 = Coin(img2);
    //    Coin coin3 = Coin(img3);
    //    
    //    vector<Coin> coinVector = { {coin1}, {coin2}, {coin3} };
    //
    //    compareCoins(coinVector);
    //
    //    for (int i = 0; i < 3; i++) {
    //        cout << "Coin" << i << " Probs" << endl;
    //        cout << "Penny% = " << coinVector[i].finalProbabilities.at(0) << endl;
    //        cout << "Nickel% = " << coinVector[i].finalProbabilities.at(1) << endl;
    //        cout << "Dime% = " << coinVector[i].finalProbabilities.at(2) << endl;
    //        cout << "Quarter% = " << coinVector[i].finalProbabilities.at(3) << endl;
    //        cout << endl;
    //    }



    return 0;
}
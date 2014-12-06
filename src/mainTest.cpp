#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "Data.h"
//#include "coin.h"
//#include "vision/binarize.cpp"
//#include "vision/label.cpp"

using namespace std;

int main(int argc, char* argv[]) {

    string imgPath = "test/coins_1.jpg";
    imshow("input image", imread(imgPath));
    Data data = Data(imgPath);
    cout << "Captured coins are worth: $" << data.sumCoins();
    

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
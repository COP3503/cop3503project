#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "coin.h"

using namespace cv;

class Data {
public:
    Data(string);
    //void getImage();
    double sumCoins();
    vector<Coin> fillPiggyBank(vector<Mat*>);
    double countDenomination(string);
    //void compareCoins(Coin, int);
    Mat mainImage;
    vector<Mat*> coinMasks;
    vector<Coin> piggyBank;
    
};

void compareCoins(vector<Coin>&);

//Data::Data(string){};

//void Data::getImage();

//vector<Coin> Data::fillPiggyBank(vector<Mat*>);

//double Data::countDenomination(string);
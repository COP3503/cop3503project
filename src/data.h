#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

class Data {
public:
    void Data(string);
    //void getImage();
    double sumCoins();
    Mat image;
    vector<Mat*> binary;
    vector<coin> piggyBank;
    
};

void Data::Data(string);

//void Data::getImage();

vector<coin> Data::fillPiggyBank(vector<Mat*>);
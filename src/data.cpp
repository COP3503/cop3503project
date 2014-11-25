#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <binarize.h>

using namespace cv;

void Data::Data(string imgPath) {
    mainImage imread(path);
    binaryArray get_hough_masks(mainImage);
    piggyBank = fillPiggyBank(binary);
}

vector<coin> Data::fillPiggyBank(vector<Mat*> binaryArray) {
    for (Mat* bin : binaryArray) {
        piggyBank.push_back(Coin(bin));
    }
}

double Data::sumCoins() {
    double value = 0;
    for (Coin coin) {
        value += coin.getDollarValue();
    }
    return value;
}
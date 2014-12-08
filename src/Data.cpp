#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Data.h"
#include "vision/binarize.cpp"
#include "vision/label.cpp"
#include "vision/visualization.cpp"

using namespace cv;

Data::Data(string imgPath) {
    mainImage = imread(imgPath);
    if (mainImage.empty()) {
        initFailed = true;
    } else {
        coinMasks = get_hough_masks(mainImage);
        piggyBank = fillPiggyBank(coinMasks);
        compareCoins(piggyBank);
        for (auto coin = piggyBank.begin(); coin != piggyBank.end(); coin++) {
            vector< map<string, double> > coinProbs = coin->getProbVector();
            string denomination = label(coinProbs);
            coin->setDenomination(denomination);
        }
    }
}

// starts the diameter comparison process
void compareCoins(vector<Coin> &piggyBank) {
    int size = piggyBank.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j) {
                piggyBank[i].compare(piggyBank[j]);
            }
        }
    }
    for (int i = 0; i < size; i++) {
        piggyBank[i].bestProb("avg");
    }
}

// initializes a coin for every image mask into a vector
vector<Coin> Data::fillPiggyBank(vector<Mat*> coinMasks) {
    for (auto mask = coinMasks.begin(); mask != coinMasks.end(); mask++) {
        piggyBank.push_back(Coin(**mask));
    }
    return piggyBank;
}

// adds the dollar value of all coins
double Data::sumCoins() {
    double value = 0;
    for (auto coin = piggyBank.begin(); coin != piggyBank.end(); coin++) {
        value += coin->getDollarValue();
    }
    return value;
}

// returns the number of coins present
int Data::getNumOfCoins() {
    return piggyBank.size();
}

// shows the user an image with all but the specified coin blacked out
void Data::displayCoin(int index) {
    if (index < piggyBank.size()) {
        string title = "Coin is a " + piggyBank[index].getDenomination();
        showCoin(mainImage, *coinMasks[index], title);
        waitKey(0);
    }
}

// shows the user all the coins, one at a time
void Data::displayAll() {
    for (int i = 0; i < getNumOfCoins(); i++) {
        string title = "Coin is a " + piggyBank[i].getDenomination();
        showCoin(mainImage, *coinMasks[i], title);
    }
    //waitKey(0);
}

// modifies the denomination and dollar value of a particular coin
void Data::correctCoin(int i, string newDenom) {
    piggyBank[i].setDenomination(newDenom);
}

// counts the number of each type of coin (I.E. "there are 2 dimes")
double Data::countDenomination(string denom) {
    double count = 0;
    for (int i = 0; i < piggyBank.size(); i++) {
        if (piggyBank[i].getDenomination().compare(denom) == 0) {
            count++;
        }
    }
    return count;
}

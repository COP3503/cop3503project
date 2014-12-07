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
    coinMasks = get_hough_masks(mainImage);
    piggyBank = fillPiggyBank(coinMasks);
    compareCoins(piggyBank); 
    for (auto coin = piggyBank.begin(); coin != piggyBank.end(); coin++) {
        vector< map<string, double> > coinProbs = coin->getProbVector();
        string denomination = label(coinProbs);
        coin->setDenomination(denomination);
        //std::cout << coin->getDenomination() << " = " << coin->getDollarValue() << std::endl;
    }
}

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
        piggyBank[i].bestProb("max");
        //piggyBank[i].printProbs();
    }
}

vector<Coin> Data::fillPiggyBank(vector<Mat*> coinMasks) {
    for (auto mask = coinMasks.begin(); mask != coinMasks.end(); mask++) {
        piggyBank.push_back(Coin(**mask));
    }
    return piggyBank;
}

double Data::sumCoins() {
    double value = 0;
    for (auto coin = piggyBank.begin(); coin != piggyBank.end(); coin++) {
        value += coin->getDollarValue();
    }
    return value;
}

int Data::getNumOfCoins() {
    return piggyBank.size();
}

void Data::displayCoin(int index) {
    while (index < piggyBank.size()) {
        string title;
        title = "Coin " + index + string(" is a ") + piggyBank[index].getDenomination();
        showCoin(mainImage, *coinMasks[index], title);
    }
}

double Data::countDenomination(string denom) {
    double count = 0;
    vector<Coin>::iterator coin;
    for (int i = 0; i < piggyBank.size(); i++) { //= piggyBank.begin(); coin != piggyBank.end(); coin++) {
        if (piggyBank[i].getDenomination().compare(denom)) {
            count++;
        }
    }
    return count;
}

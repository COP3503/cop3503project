#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <cmath>
#include "coin.h"

using namespace cv;
using namespace std;

//Ideal CoinStruct initialization
struct CoinStruct {
  double Ratio;
  double Difference;
  double ScaledDifference;
  string CoinA;
  string CoinB;
} Ideal [16];

//Constructor
Coin::Coin(Mat mask){
  Mask = mask;
  int width = Mask.cols;
  int height = Mask.rows;
  bool coinFlag = false;
  int counter = 0;
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      if(Mask.at<int>(i,j) == -1){
	coinFlag = true;
	counter++;
	break;
      }
    }
    coinFlag = false;
  }
  diameter = counter;
  denomination = "unknown";
  dollarValue = 0;
};

void Coin::setDenomination(string name){
  if (name=="quarter") dollarValue = .25;
  if (name=="dime") dollarValue = .1;
  if (name=="nickle") dollarValue =.05;
  if (name=="penny") dollarValue =.01;
  denomination = name;
};

string Coin:: getDenomination(){
  return denomination;
};
  
double Coin::getDollarValue(){
  return dollarValue;
};
  
double Coin::getDiameter(){
  return diameter;
};

map<string,double> Coin::getDiameterMap(){
  return diameterMap;
};

Mat Coin::getMask(){
  return Mask;
};

void Coin::updateProbablities(string denomination, double Prob){
  if (denomination.compare("penny")==0) allProbabilities[0].push_back(Prob);
  if (denomination.compare("nickel")==0) allProbabilities[1].push_back(Prob);
  if (denomination.compare("dime")==0) allProbabilities[2].push_back(Prob);
  if (denomination.compare("quarter")==0) allProbabilities[3].push_back(Prob);
};

void Coin::bestProb(){
  string name[4] = {"penny","nickel","dime","quarter"};
  double max;
  for(int i = 0; i<4; i++){
    int size = allProbabilities[i].size();
    if(size == 0){
      max = 0;
    }
    else{
      max = allProbabilities[i].at(0);
      for(int j = 1; j<=size-1; j++){
	if(allProbabilities[i].at(j) > max){
	  max = allProbabilities[i].at(j);
	}
      }
      finalProbabilities.push_back(max);
      diameterMap[name[i]]=max;
    }
  }
};

void Coin::printProbs(){
  for(int i = 1; i<=4; i++){
    int size = allProbabilities[i].size();
    for(int j = 1; j<=size; j++){
    }
  }

  int size2 = finalProbabilities.size();

  for(int j = 1; j<=size2; j++){
  }
};

void Coin::compare(Coin B){

  //Ideal coin struct initialization
  double value[4] = {.75, .835, .705, .955};
  string name[4] = {"penny","nickel","dime","quarter"};

  for(int i = 0; i<16; i++){
    Ideal[i].Ratio = value[i/4]/value[i%4];
    Ideal[i].CoinA = name[i/4];
    Ideal[i].CoinB = name[i%4];
    Ideal[i].Difference = abs(value[i/4]-value[i%4]);
    Ideal[i].ScaledDifference = Ideal[i].Difference/((value[i/4]+value[i%4])/2);
  }

  //Coin Compare method
  double dA = diameter;
  double dB = B.getDiameter();
  double ratio = dA/dB;
  double scaledDifference = abs(dA-dB)/((dA+dB)/2);
  double sProb, rProb, aProb;

  for(int i = 0; i<16; i++){
    if(Ideal[i].Ratio != 1){
      rProb = 1 - abs(ratio - Ideal[i].Ratio);
      sProb = 1 - abs(scaledDifference - Ideal[i].ScaledDifference);
      aProb = abs((rProb + sProb)/2);
      updateProbablities(Ideal[i].CoinA,aProb);
      B.updateProbablities(Ideal[i].CoinB,aProb);
    }
  }
};

//Diameter compare
/*void compareCoins(Coin array[], int size){
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
  }*/

//Test Case
/*int main(){

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
  return 0;
  }*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <cmath>

using namespace cv;

using namespace std;

struct CoinStruct {
  double Ratio;
  double Difference;
  double ScaledDifference;
  string CoinA;
  string CoinB;
} Ideal [16];

class Coin{
public:
  int diameter;
  string denomination;
  int dollarValue;
  Mat Mask;

  //order starting from 1: penny, nickel, dime, quarter
  vector<double> allProbabilities[4];
  vector<double> finalProbabilities;

  map<string,double> diameterMap;

  //Constructor
  Coin(Mat mask){
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
  }

  //Sets the denomination for a coin
  void setDenomination(string name){
    if (name=="quarter") dollarValue += .25;
    if (name=="dime") dollarValue += .1;
    if (name=="nickle") dollarValue +=.05;
    if (name=="penny") dollarValue +=.01;
    denomination = name;
  }

  string getDenomination(){
    return denomination;
  }

  double getDiameter(){
    return diameter;
  }

  map<string,double> getDiameterMap(){
    return diameterMap;
  }

  Mat getMask(){
    return Mask;
  }

  //Adds a probability of a coin type to its appropriate coin vector
  void updateProbablities(string denomination, double Prob){
    if (denomination.compare("penny")==0) allProbabilities[0].push_back(Prob);
    if (denomination.compare("nickel")==0) allProbabilities[1].push_back(Prob);
    if (denomination.compare("dime")==0) allProbabilities[2].push_back(Prob);
    if (denomination.compare("quarter")==0) allProbabilities[3].push_back(Prob);
  }

  //Finds the best probability of each coin type for a coin and adds them to the finalProbabilites vector
  void bestProb(){
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
  }

  //Compare 2 coins and find relative confidence
  void compare(Coin B){

    //Creat struct with all ideal coin values
    double value[4] = {.75, .835, .705, .955};
    string name[4] = {"penny","nickel","dime","quarter"};

    for(int i = 0; i<16; i++){
      Ideal[i].Ratio = value[i/4]/value[i%4];
      Ideal[i].CoinA = name[i/4];
      Ideal[i].CoinB = name[i%4];
      Ideal[i].Difference = abs(value[i/4]-value[i%4]);
      Ideal[i].ScaledDifference = Ideal[i].Difference/((value[i/4]+value[i%4])/2);
    }

    //Compare Method
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
  }
};





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
  /********Variables and objects********/
  int diameter;
  string denomination;
  int dollarValue;
  Mat Mask;

  //order starting from 1: penny, nickel, dime, quarter
  vector<double> allProbabilities[4];
  vector<double> finalProbabilities;
  map<string,double> diameterMap;

  //Constructor
  Coin(Mat mask);

  /********Methods********/

  //Sets the denomination for a coin
  void setDenomination(string name);

  string getDenomination();
  
  double getDollarValue();

  double getDiameter();

  map<string,double> getDiameterMap();

  Mat getMask();

  //Adds a probability of a coin type to its appropriate coin vector
  void updateProbablities(string denomination, double Prob);

  //Finds the best probability of each coin type for a coin and adds them to the finalProbabilites vector
  void bestProb();

  //Compare 2 coins and find relative confidence
  void compare(Coin B);
};





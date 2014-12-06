#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <cmath>

using namespace cv;
using namespace std;

class Coin{
public:
  /********Variables and objects********/
  int diameter;
  string denomination;
  double dollarValue;
  Mat Mask;

  //order starting from 1: penny, nickel, dime, quarter
  vector<double> allProbabilities[4];
  vector<double> finalProbabilities;
  vector< map<string,double> > probVector;

  //Constructor
  Coin(Mat mask);

  /********Methods********/

  //Sets the denomination for a coin
  void setDenomination(string name);
  
  void appendProbVector(map<string, double>);

  string getDenomination();
  
  double getDollarValue();

  double getDiameter();

  vector< map<string,double> > getProbVector();

  Mat getMask();

  //Adds a probability of a coin type to its appropriate coin vector
  void updateProbablities(string denomination, double Prob);

  //Finds the best probability of each coin type for a coin and adds them to the finalProbabilites vector takes in an option of either "max" or "avg" to determine how the final probabilty is calculated
  void bestProb(string option);

  //Compare 2 coins and find relative confidence
  void compare(Coin B);

  //troubleshooting function
  void printProbs();
};

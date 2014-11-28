#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>

using namespace std;

class Coin{
private:
  int diameter;
  string denomination;
  int dollarValue;

  //order starting from 1: penny, nickel, dime, quarter
  vector<double> allProbablilites[4];
  vector<double> finalProbablities;

  map<string,double> diameterMap;
}



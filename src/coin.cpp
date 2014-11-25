#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;


//Constructor
Coin(Mat mask){
  int size = mask.size;
  int height = size.height;
  int width = size.width;
  bool coinFlag = false;
  int counter = 0;
  for(int i = 0; int < height; i++){
    for(int j = 0; int < width; j++){
      if(mask(i,j) == 255){
	coinFlag = true;
	cointer++;
      }
    }
    coinFlag = false;
  }
  diameter = counter;
  value = 'no coin';
}

//diameter compare
void compareCoins(Coin A, Coin B){

  struct CoinRatios {
    double Ratio;
    string CoinA;
    string CoinB;
  } Ratios [16];

  double ratio = A.diameter/B.diameter;
  for(int i = 0; i<16; i++){
    if(ratio = Ratios[i].ratio){
      A.value = Ratios[i].CoinA;
      B.value = Ratios[i].CoinB;
    }
  }
};

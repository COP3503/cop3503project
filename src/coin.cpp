#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>

using namespace std;


struct CoinStruct {
  double Ratio;
  string CoinA;
  string CoinB;
} Ratios [16];

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
  denomination = 'unknown';
  dollarValue = 0;
  diameterMap = 
}

void setDenomination(Coin a, string name){
  //    if (name=="Dollar-coin") a.dollarValue += 1;
  //    if (name=="Half-dollar") a.dollarValue += .5;
    if (name=="quater") a.dollarValue += .25;
    if (name=="dime") a.dollarValue += .1;
    if (name=="nickle") a.dollarValue +=.05;
    if (name=="penny") a.dollarValue +=.01;
    denomination = name;
  }
}

string getDenomination(Coin a){
  return a.denomination;
}

//diameter compare
void compareCoins(Coin[] array){

  int size = array.size;
  //Creat struct with all coin values
  double ratio[4] = {.75, .835, .705, .955};

  string name[4] = {'penny','nickel','dime','quarter'};

  for(int i = 0; i<4; i++){
    for(int j = 1; j<5; j++){
      Ratios[i*j].Ratio = ratio[i]/ratio[j-1];
      Ratios[i*j].CoinA = name[i];
      Ratios[i*j].CoinB = name[j-1];
    }
  }

  void coinCompare(Coin A, Coin B){
    double ratio = A.diameter/B.diameter;
    for(int i = 0; i<16; i++){
      if(ratio = Ratios[i].ratio && ratio != 1){
	A.value = Ratios[i].CoinA;
	B.value = Ratios[i].CoinB;
      }
    }
  }
  void arrayCompare(Coin[] array){
};










#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <cmath>

using namespace std;


struct CoinStruct {
  double Ratio;
  double Difference;
  double ScaledDifference;
  string CoinA;
  string CoinB;
} Ideal [16];

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

  //Creat struct with all coin values
  double value[4] = {.75, .835, .705, .955};
  string name[4] = {"penny","nickel","dime","quarter"};

  for(int i = 0; i<16; i++){
    Ideal[i].Ratio = value[i/4]/value[i%4];
    Ideal[i].CoinA = name[i/4];
    Ideal[i].CoinB = name[i%4];
    Ideal[i].Difference = abs(value[i/4]-value[i%4]);
    Ideal[i].ScaledDifference = Ideal[i].Difference/((value[i/4]+value[i%4])/2);
  }

  //Compare 2 coins and find relative confidence
  void compare(Coin A, Coin B){
    dA = A.diameter;
    dB = B.diameter;
    double ratio = dA/dB;
    double scaledDifference = abs(dA-dB)/((dA+dB)/2);
    double sProb, rProb, aProb;

    for(int i = 0; i<16; i++){
      if(Ideal[i].ratio != 1){
	rProb = 1 - abs(ratio - Ideal[i].Ratio);
	sProb = 1 - abs(scaledDifference - Ideal[i].ScaledDifference);
	aProb = (rProb + sProb)/2;
	updateProbablities(A,Ideal[i].CoinA,aProb);
	updateProbablities(B,Ideal[i].CoinB,aProb);
      }
    }
  }

  //Adds a probability of a coin type to its appropriate coin vector
  void updateProbablities(Coin A, string denomination, double Prob){
    if (denomination=="penny") A.allProbabilities[1].push_back(Prob);
    if (denomination=="nickel") A.allProbabilities[2].push_back(Prob);
    if (denomination=="dime") A.allProbabilities[3].push_back(Prob);
    if (denomination=="quarter") A.allProbabilities[4].push_back(Prob);
  }

  //Finds the best probability of each coin type for a coin and adds them to the finalProbabilites vector
   void bestProb(Coin coin){
    double max;
    for(int i = 0; i<4; i++){
      int size = coin.probabilites[i].size;
      for(int j = 0; j<size-1; j++){
	if(coin.allProbabilities[i].at(j+1) > coin.allProbabilities[i].at(i)){
	  max = coin.allProbabilities[i].at(j+1);
	}
	else{
	  max = coin.allProbabilities[i].at(i);
	}
      }
      coin.finalProbablities.push_back(max);
    }
    return probs;
  }

  int size = Coin[].size;
  for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
      if(i != j){
	compare(Coin[i], Coin[j]);
      }
    }
  }

  for(int i = 0; i<size; i++){
best

};










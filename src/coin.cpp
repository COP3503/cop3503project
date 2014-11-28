#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <cmath>

using namespace cv;


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

  //order starting from 1: penny, nickel, dime, quarter
  vector<double> allProbablilites[4];
  vector<double> finalProbablities;

  //map<string,double> diameterMap;
  //Constructor
  Coin(Mat mask){
    int height = mask.cols;
    int width = mask.rows;
    bool coinFlag = false;
    int counter = 0;
    for(int i = 0; i < height; i++){
      for(int j = 0; i < width; j++){
	if(mask(i,j) == 255){
	  coinFlag = true;
	  cointer++;
	}
      }
      coinFlag = false;
    }
    diameter = counter;
    denomination = "unknown";
    dollarValue = 0;
    //diameterMap = 
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

  string getDenomination(Coin a){
    return a.denomination;
  }
};

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

  int size = array.size;
  for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
      if(i != j){
	compare(array[i], array[j]);
      }
    }
  }

  for(int i = 0; i<size; i++){
    bestProb(array[i]);
  }
};

int main(){

  Coin coinArray[3];

  img imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_1.png");
  Coin coinArray[1] = new Coin(img);
  img imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_2.png");
  Coin coinArray[2] = new Coin(img)
  img imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_3.png");
  Coin coinArray[3] = new Coin(img);

  compareCoins(coinArray);

  return 0;
}










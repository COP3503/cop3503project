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

  //order starting from 1: penny, nickel, dime, quarter
  vector<double> allProbabilities[4];
  vector<double> finalProbabilities;
  vector<double> pProb;
  vector<double> nProb;
  vector<double> dProb;
  vector<double> qProb;

  //map<string,double> diameterMap;
  //Constructor
  Coin(Mat mask){
    int height = mask.cols;
    int width = mask.rows;
    bool coinFlag = false;
    int counter = 0;
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
	//	cout<<mask.at<int>(i,j)<<endl;
	if(mask.at<int>(i,j) == -1){
	  coinFlag = true;
	  counter++;
	  break;
	  //  cout<<counter<<endl;
	}
      }
      coinFlag = false;
    }
    diameter = counter;
    cout<<"diameter = "<<diameter<<endl;
    denomination = "unknown";
    dollarValue = 0;
    //diameterMap = 
  }

  void setDenomination(string name){
    //    if (name=="Dollar-coin") a.dollarValue += 1;
    //    if (name=="Half-dollar") a.dollarValue += .5;
    if (name=="quater") dollarValue += .25;
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

  //Adds a probability of a coin type to its appropriate coin vector
  void updateProbablities(string denomination, double Prob){
    //    Coin A;
    //  cout<<"Prob = "<<Prob<<endl;
    //  cout<<"denomination= "<<denomination<<endl;
    if (denomination.compare("penny")==1)allProbabilities[1].push_back(Prob);
    if (denomination.compare("nickel")==1) allProbabilities[2].push_back(Prob);
    if (denomination.compare("dime")==1) allProbabilities[3].push_back(Prob);
    if (denomination.compare("quarter")==1)qProb.push_back(Prob);
  }

  //Finds the best probability of each coin type for a coin and adds them to the finalProbabilites vector
  void bestProb(){
    double max;
    for(int i = 1; i<=4; i++){
      int size = allProbabilities[i].size();
      //    cout<<"sizeAll = "<<size<<endl;
      for(int j = 1; j<=size-1; j++){
	//	cout<<"prob j = "<<allProbabilities[i].at(j-1)<<endl;
	//	cout<<"prob j+1 = "<<allProbabilities[i].at(j)<<endl;
	//	cout<<"j = "<<j<<endl;
	if(allProbabilities[i].at(j-1) > allProbabilities[i].at(j)){
	  max = allProbabilities[i].at(j-1);
	}
	else{
	  max = allProbabilities[i].at(j);
	}
      }
      finalProbabilities.push_back(max);
      cout<<"pushed "<<max<<" for "<<i<<endl;
    }
  }

  //troubleshooting function
  void printProbs(){
    for(int i = 1; i<=4; i++){
      int size = allProbabilities[i].size();
      cout<<"Coin"<<i<<endl;
      for(int j = 1; j<=size; j++){
	cout<<"index"<<j<<" = "<<allProbabilities[i].at(j-1)<<endl;
      }
      cout<<endl;
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

    double dA = diameter;
    double dB = B.getDiameter();
    double ratio = dA/dB;
    cout<<"ratio = "<<ratio<<endl;
    double scaledDifference = abs(dA-dB)/((dA+dB)/2);
    double sProb, rProb, aProb;

    for(int i = 0; i<16; i++){
      if(Ideal[i].Ratio != 1){
	rProb = 1 - abs(ratio - Ideal[i].Ratio);
	sProb = 1 - abs(scaledDifference - Ideal[i].ScaledDifference);
	aProb = (rProb + sProb)/2;
	updateProbablities(Ideal[i].CoinA,aProb);
	B.updateProbablities(Ideal[i].CoinB,aProb);
      }
    }
  }
};


//diameter compare
void compareCoins(Coin array[], int size){

  for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
      if(i != j){
	array[i].compare(array[j]);
      }
    }
  }

  for(int i = 0; i<size; i++){
    array[i].printProbs();
    array[i].bestProb();
  }
}

int main(){


  Mat img1 = imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_1.png");
  Mat img2 = imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_2.png");
  Mat img3 = imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_3.png");

  //  Coin* test = new Coin(img1);

  Coin coinArray[3]{{img1},{img2},{img3}};

  /*  Mat img;
      img = imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_1.png");
      Coin coinArray[1] = new Coin(img);
      img imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_2.png");
      Coin coinArray[2] = new Coin(img)
      img imread("/home/mani/School/UF/Fall 2014/COP3503/Final Project/cop3503project/test/coins_1_mask_3.png");
      Coin coinArray[3] = new Coin(img);*/

  cout<<"Coin Probs"<<endl; 

  compareCoins(coinArray,3);

  for(int i = 1; i<=3; i++){
     cout<<"Coin"<<i<<" Probs"<<endl; 

    cout<<"size = "<<coinArray[i].finalProbabilities.size()<<endl;

    cout<<"Penny% = "<<coinArray[i].finalProbabilities.front()<<endl;
    cout<<"Nickel% = "<<coinArray[i].finalProbabilities.at(2)<<endl;
    cout<<"Dime% = "<<coinArray[i].finalProbabilities.at(3)<<endl;
    cout<<"Quarter% = "<<coinArray[i].finalProbabilities.at(4)<<endl;
  }
  return 0;
}










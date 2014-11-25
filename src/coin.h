#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;

class Coin{
public:
  int diameter;
  string value;

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
  }

  value = 'no coin';
};

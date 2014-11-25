#include <iostream>
#include <string>

using namespace std;

string getCoin(int length){ //redo function to accuratley get each type of coin recorded
    return "Quater";
}

double getValue(int length) { //modify this function to work with rest of the project
    double value = 0;
    while(length>0){
        string x = getCoin(1);
        if (x=="Dollar-coin") value += 1;
        if (x=="Half-dollar") value += .5;
        if (x=="Quater") value += .25;
        if (x=="Dime") value += .1;
        if (x=="Nickle") value +=.05;
        if (x=="Penny") value +=.01;
        length--;
    }
    return value;
}

int getLength() {
    return 1; //remove this and replace this with a way to get the number of 
    //coins that were counted
}

string getPicture() {
    string myString;
    getline(cin, myString);
    unsigned int len = myString.length();
    string sub = myString.substr(len-4, len);
    if (sub==".bmp" || sub==".dib" || sub== "jpeg" || sub== ".jpg" || sub == ".jpe" || sub== ".jp2" || sub== ".png" || sub== ".pbm" || sub== ".pgm" || sub == ".ppm" || sub.substr(1,4)==".sr" || sub==".ras" || sub== "tiff" || sub== ".tif") {	
    	return myString;
    }
    return "void";		
}

int displayInterface() {
    cout << "Welcome to the coin counter program!" << endl << endl; 
    cout << "Please upload picture to be analyzed: ";
    cout << "\n";
    string fileName=getPicture();
    if (fileName=="void") {
	cout << "Invalid picture inputted\n";
	return 0;
    }	
    cout << "\n\n";
    int length = getLength();
    cout << "The value of the coins on display is $" << getValue(length) << "\n";
    return 0;
}

int main()
{
    displayInterface();    
   return 0;
}

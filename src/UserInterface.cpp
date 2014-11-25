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
    return myString;
}

void displayInterface() {
    cout << "Welcome to the coin counter program!" << endl << endl; 
    cout << "Please upload picture to be analyzed: ";
    cout << "\n";
    getPicture();	
    cout << "\n\n";
    int length = getLength();
    cout << "The value of the coins on display is $" << getValue(length) << "\n";
}

int main()
{
    displayInterface();    
   return 0;
}

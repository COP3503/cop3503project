#include <iostream>
#include <string>
#include "Data.h"

using namespace std;

string getPicture() {
    string myString;
    getline(cin, myString);
    unsigned int len = myString.length();
    string sub = myString.substr(len - 4, len);
    string subl = myString.substr(len - 5, len);
    if (sub == ".bmp" || sub == ".dib" || subl == ".jpeg" || sub == ".jpg" || sub == ".jpe" || sub == ".jp2" || sub == ".png" || sub == ".pbm" || sub == ".pgm" || sub == ".ppm" || sub.substr(1, 4) == ".sr" || sub == ".ras" || subl == ".tiff" || sub == ".tif") {
        return myString;
    }
    return "void";
}

string displayInterface() {
    cout << "Welcome to COPper, a coin counting program!" << endl << endl;
    cout << "To get started, please take an picture of some coins.\n\n";
    cout << "For best results, the image should:\n";
    cout << "    + Be taken from directly above the coins\n";
    cout << "    + Have a background that contrasts with the coins\n";
    cout << "    + Depict no overlapping coins\n";
    cout << "    + Avoid partial coins (coins that are partially out of the image)\n\n";
    cout << "With your image now on your computer, please type the path and filename:\n\n";
    cout << "Image Path: ";
    string fileName = getPicture();
    if (fileName == "void") {
        cout << "Invalid picture inputted\n\n";
        return displayInterface();
    }
    cout << "\n\n";
    return fileName;
}

int mainMenu(Data &data) {
    int n = 1;
    while (n != 0) {
        int length = data.getNumOfCoins();
        cout << "We have detected " << length << " coin(s), with a total value of $" << data.sumCoins() << "\n";
        cout << "\nFrom here you can review our analysis by choosing one of the following options:\n";
        cout << "    1 : Show me each of the coins\n";
        cout << "    2 : Show me an individual coin\n";
        cout << "    3 : Show me the denominational breakdown (how many coins of each type)\n";
        cout << "    4 : Correct a mis-identified coin\n";
        cout << "    5 : Recalculate the total value\n";
        cout << "    0 : Exit menu\n\n";
        cout << "Please make a choice: ";
        cin >> n;
        cout << "\n\n";
        if (n == 1) data.displayAll();
        else if (n == 2) {
            int choice = 0;
            cout << "We have detected " << data.getNumOfCoins() << " coin(s).\n"; //replace
            cout << "Please select one by inputing a number between 0 and " << data.getNumOfCoins() << "\n";
            cout << "Show me coin: ";
            cin >> choice;
            if (choice < 0 || choice > data.getNumOfCoins())
                cout << "Displaying coin " << choice << "\n";
            data.displayCoin(choice);
        } else if (n == 3) {
            cout << "Our analysis has detected a total of " << data.getNumOfCoins() << " coins of the following denominations:\n";
            cout << "Quarters: " << data.countDenomination("quarter") << "\n";
            cout << "Dimes: " << data.countDenomination("dime") << "\n";
            cout << "Nickels: " << data.countDenomination("nickel") << "\n";
            cout << "Pennies: " << data.countDenomination("penny") << "\n\n";
        } else if (n == 4) {
            int input = 0;
            int inputTwo = 0;
            cout << "Whoops, we may have made an error. Choose a coin to re-identify.\n";
            cout << "Please select a coin by entering a number between 0 and" << data.getNumOfCoins() << "\n";
                    cout << "Coin to correct:";
            cin >> input;
            if (input >= 0 && input < data.getNumOfCoins()) {
                data.displayCoin(input);
                cout << "\n\nSelect the proper denomination: \n";
                cout << "    1 : Quarter\n    2 : Dime\n    3 : Nickel\n    4 : Penny\n    0 : NO CHANGE\n";
                cout << "Make a choice:";
                cin >> inputTwo;
                string coins[4] = {"quarter", "dime", "nickel", "penny"};
                if (inputTwo > 0 && inputTwo < 5) {
                    data.correctCoin(input, coins[ (inputTwo - 1) ]);
                    cout << "\n\nYour revised total is $" << data.sumCoins() << "\n";
                }
            } else {
                cout << "No change made.\n";
            }
        } else if (n == 5) {
            int lengthc = data.getNumOfCoins();
            cout << "We have detected " << lengthc << " coin(s), with a total value of $" << data.sumCoins() << "\n";
        } else if (n == 0) {
            return 0;
        } else {
            cout << "Unrecognized option, try again.\n";
        }
    }
    return 0;
}

int main() {
    string imagePath = displayInterface();
    Data data = Data(imagePath);
    mainMenu(data);
    return 0;
}

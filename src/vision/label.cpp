// #include <iterator>
#include <string>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include "vision.h"

using namespace cv;

// void update_probability_map(std::map<std::string, double> &input_map, std::map<std::string, double> &tracking_map);


void update_probability_map(std::map<std::string, double> &input_map, std::map<std::string, double> &tracking_map) {
    /* Once a labelling function generates a probability map, add that map to the non-normalized probability map */

    std::map<std::string, double>::iterator it;
    for (it = tracking_map.begin(); it != tracking_map.end(); it++) {
        // it->second += input_map[it->first];
    }
}

std::string label(std::vector< std::map< std::string, double > > maps) {
    /* "maps" is a vector that contains a vector of maps which the labeller will label */

    // Non-normalized probability sum
    std::map<std::string, double> probabilities = {
        {"penny", 0.0}, {"nickel", 0.0}, {"dime", 0.0}, {"quarter", 0.0}
    };

    // Aggregate probabilities
    for (int i = 0; i < maps.size(); i++) {
        update_probability_map(maps[i], probabilities);
    }

    // Choose maximum (Does not check for edge-cases, assumes we've made sufficient distinction)
    double maximum = 0.0;
    std::string choice = ""; // Will contain a string like "penny"
    std::map<std::string, double>::iterator it;
    for (it = probabilities.begin(); it != probabilities.end(); it++) {
        if (it->second > maximum) {
            maximum = it->second;
            choice = it->first;
        }
    }
    return choice;
}
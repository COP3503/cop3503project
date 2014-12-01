#include <string>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>


void update_probability_map(std::map<std::string, double>  input_map, std::map<std::string, double> & tracking_map) {
    /* Once a labelling function generates a probability map, add that map to the non-normalized probability map */
    std::map<string, double>::iterator it;
    for (it = tracking_map.begin(); it != tracking_map.end(); it++)
    {
        it->second += input_map[it->first];
    }
}

std::string label(Mat & mask, Mat & original_image) {
    // Non-normalized probability sum
    std::map<std::string, double> probabilities = {
        {"penny", 0.0}, {"nickel", 0.0}, {"dime", 0.0}, {"quarter", 0.0}
    };
    std::vector< std::map<std::string, double> >
    maps.push_back(diameter_label(mask, original_image));
    maps.push_back(color_label(mask, original_image));


    // Aggregate probabilities
    for (int i = 0; i < maps.length(); i++) {
        update_probability_map(maps[i], probablities);
    }

    // Choose maximum (Does not check for edge-cases, assumes we've made sufficient distinction)
    double maximum = 0.0;
    std::string choice = ""; // Will contain a string like "penny"
    for (it = probabilities.begin(); it != probabilities.end(); it++)
    {
        if (it->second > maximum) {
            maximum = it->second;
            choice = it->first;
        }
    }

    return choice;
}
#ifndef BINARIZE_COP3503_H_
#define BINARIZE_COP3503_H_

#include <string>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>

std::vector<cv::Mat*> get_hough_masks(cv::Mat);

/* TODOs:

    ## 
    For coin-circle similarity, fit an oval, "O" to the mask, "M".

    size(M \ O) = diff [where \ is the set difference operator]
    if diff > 0.1 * area(O): Not a coin or an oval at all!

    ################

    Harr cascade classifier
    Machine learning

    Someone needs to find training images


*/
    
#endif
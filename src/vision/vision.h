#ifndef BINARIZE_COP3503_H_
#define BINARIZE_COP3503_H_

#include <string>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>

/* binarize.cpp --------------------------- */
std::vector<cv::Mat*> get_hough_masks(cv::Mat);
/* ---------------------------------------- */

/* label.cpp --------------------------- */
void update_probability_map(std::map<std::string, double> &input_map, std::map<std::string, double> &tracking_map);
std::string label(std::vector< std::map< std::string, double > > maps);
/* ------------------------------------- */

/* visualization.cpp-------------------- 
    Contains tools for visualizing images
*/
void showCoin(cv::Mat original_image, cv::Mat mask);
/* ------------------------------------- */


/* TODOs:

    ## 
    For coin-circle similarity, fit an oval, "O" to the mask, "M".

    size(M \ O) = diff [where \ is the set difference operator]
    if diff > 0.1 * area(O): Not a coin or an oval at all!

    Notes:

        Segmentation:
            Watershed for segmentation is a reasonable approach, but will not work on complex backgrounds
            Likewise, houghcircles will fail on complex backgrounds

        
        Labelling:

            Real diameter is viewing angle insensitive
            HSV color [H] is generally lighting insensitive and always viewing angle insensitive
            -- Apply Ohtsu threshhold
            -- Full histogram matching will work better, can we do it?

            -- Note the 2D Fast Otsu method

            Perspective/affine transform of the simplest inscribing quadrilateral will give a top-down view of the coin
            -- Then, can use Haar cascade



    ################

    Harr cascade classifier
    Machine learning

    Someone needs to find training images

*/
    
#endif
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "vision.h"
#include <string.h>

using namespace cv;

void showCoin(Mat original_image, Mat mask, string title) {
    /* showCoin(original image, binary mask)
    You will have to call your own waitkey(0) outside of this function.
        Ex:
            showCoin(input_image, *masks[j]);
            waitKey(0);
     */
    Mat masked;
    original_image.copyTo(masked, mask);
    namedWindow(title, WINDOW_AUTOSIZE);
    imshow(title, masked);
    cvWaitKey(0);
}

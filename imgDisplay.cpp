#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

int imgDisplay(string path, string title) {
    Mat image;
    image = imread(path);

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    namedWindow(title, CV_WINDOW_AUTOSIZE);
    imshow(title, image);

    waitKey(0);

    return 0;
}

int imgDisplay(Mat image, string title) {
    namedWindow(title, CV_WINDOW_AUTOSIZE);
    imshow(title, image);

    waitKey(0);

    return 0;
}

int main() {
    printf("Printing image using path function.\n");
    string path = "./test/test.jpg";
    int success = imgDisplay(path, "Test Image");
    if (success == 0) {
        printf("Test Passed \n");
    } else {
        printf("Test Failed");
    }
    printf("Printing image using image function.\n");
    Mat image = imread(path);
    success = imgDisplay(image, "Test Image");
    if (success == 0) {
        printf("Test Passed \n");
    } else {
        printf("Test Failed");
    }
}

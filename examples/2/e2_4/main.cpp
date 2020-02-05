// Example 2_4 : OpenCV example
// Created by Oleksiy Grechnyev 2017

#include <iostream>

#include <opencv2/opencv.hpp>

int main(){
    using namespace std;
    
    // Open the camera
    cv::VideoCapture cam(cv::CAP_ANY);
    if (!cam.isOpened())
        throw runtime_error("Cannot open camera");
    
    for (;;) {
        // Read frame
        cv::Mat img;
        cam.read(img);
        
        // Select the central roi and apply photo negative
        int w = img.cols, h = img.rows;
        cv::Mat m(img, cv::Rect(w/3, h/3, w/3, h/3));
        cv::bitwise_not(m, m);
        
        // Show frame
        cv::imshow("img", img);
        if (27 == cv::waitKey(1))
            break;
    }
    
    return 0;
}

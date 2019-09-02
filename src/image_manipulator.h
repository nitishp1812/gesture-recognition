#ifndef IMAGE_MANIPULATOR_H
#define IMAGE_MAINPULATOR_H

#include <vector>

#include "ofxCv.h"

// Method to draw a box on the given image
cv::Mat DrawBox(cv::Mat& camera_image);

// Method to get the pixels from the box from the given image
cv::Mat GetHandPixels(cv::Mat& image_data);

// Method to preprocess the data for classification
void PreprocessImage(cv::Mat& hand_image);

cv::Mat GetContours(cv::Mat& hand_image);

#endif

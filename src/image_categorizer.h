#ifndef IMAGE_CATERORIZER_H
#define IMAGE_CATEGORIZER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "image_manipulator.h"

#include <opencv2/opencv.hpp>

class Categorizer {

    // Names of the files which store the required data for classification based on the user input
    const std::string kFileName = "right_images.txt";

    // Variable to store the images to compare the user input with for classification
    std::vector<cv::Mat> images_to_compare_;

    // Method to get the difference between two images
    double GetDifference(cv::Mat image_1, cv::Mat image_2);

    // Method to generate the required files for classification
    void GenerateFiles();

    // Method to load the image files from the stored jpg files
    void LoadImages();

    // Method to get the predicted character from the label
    std::string GetPredicted(int label);

  public:

    // Method to initialize the classifier's parameters
    void Initialize();

    // Method to get the predicted string based on comparisons
    std::string Compare(cv::Mat user_image);
};

#endif

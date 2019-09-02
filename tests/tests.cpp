#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"

#include "../src/image_categorizer.h"
#include "src/image_manipulator.h"

TEST_CASE("Image manipulator test") {
    cv::Mat test_image = cv::imread("../gestures/1.jpg");
    cv::Mat test_input;
    cv::resize(test_image, test_input, cv::Size(640, 480));

    SECTION("Draw Box Test") {
        cv::Mat altered = DrawBox(test_input);

        REQUIRE(altered.rows == test_input.rows);
        REQUIRE(altered.cols == test_input.cols);
    }

    SECTION("Get Hand Pixels Test") {
        cv::Mat hand = GetHandPixels(test_input);

        REQUIRE(hand.rows == 300);
        REQUIRE(hand.cols == 300);
    }

    SECTION("Preprocess Test") {
        PreprocessImage(test_input);

        REQUIRE(test_input.rows == 50);
        REQUIRE(test_input.cols == 50);
        REQUIRE(test_input.channels() == 1);
    }
}

TEST_CASE("Categorizer test") {
    
    Categorizer categorizer;
    categorizer.Initialize(true);

    cv::Mat user_image = cv::imread("../gestures/0/1.jpg", cv::IMREAD_GRAYSCALE);

    std::string o = categorizer.Compare(user_image);

    std::cout << "\n" << user_image;
}

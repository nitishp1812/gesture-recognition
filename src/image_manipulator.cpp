#include "image_manipulator.h"

cv::Mat DrawBox(cv::Mat& camera_image) {
    cv::Mat flipped_image;

    // flip the image
    cv::flip(camera_image, flipped_image, 1);

    // draw the box
    cv::Rect box = cv::Rect(300, 50, 300, 300);
    cv::rectangle(flipped_image, box, cv::Scalar(0, 255, 0));

    return flipped_image;
}

cv::Mat GetHandPixels(cv::Mat& image_data) {
    cv::Mat hand_data = image_data(cv::Range(50, 350), cv::Range(300, 600)).clone();

    return hand_data;
}

void PreprocessImage(cv::Mat& hand_image) {
    cv::Mat hsv_image, skin_data, dilated_image, blurred_image, resized_image;

    // change the color format
    cv::cvtColor(hand_image, hsv_image, cv::COLOR_RGB2HSV);

    // filter the image to retain the pixels in the skin range
    std::vector<int> skin_range_lower{0, 20, 70};
    std::vector<int> skin_range_upper{20, 255, 255};
    cv::inRange(hsv_image, skin_range_lower, skin_range_upper, skin_data);

    // Dilate and blur the image for better results
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
    cv::dilate(skin_data, dilated_image, kernel, cv::Point(-1, -1), 4);

    cv::GaussianBlur(dilated_image, blurred_image, cv::Size(5, 5), 100);
    cv::resize(blurred_image, resized_image, cv::Size(150, 150));

    hand_image = resized_image;
}

cv::Mat GetContours(cv::Mat& hand_image) {
    std::vector<cv::Mat> contours;

    // find all contours in the image
    cv::findContours(hand_image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // get the contour with the max area
    cv::Mat max_contour;
    double max_contour_area = 0.0;

    for (cv::Mat contour : contours) {
        double contour_area = cv::contourArea(contour);

        if (max_contour_area < contour_area) {
            max_contour_area = contour_area;
            max_contour = contour;
        }
    }

    // get the convex hull for the contour with the max area
    cv::Mat convex_hull; 
    cv::convexHull(max_contour, convex_hull);

    // save the max contour and convex hull to a vector fro use later
    std::vector<cv::Mat> contours_to_draw = {max_contour, convex_hull};

    // create a blank image of size as the input size
    cv::Mat drawing = cv::Mat::zeros(hand_image.size(), CV_8UC1);

    // a white line color
    cv::Scalar line_color = cv::Scalar(255);

    // draw the max contour and the convex hull on the blank image
    cv::drawContours(drawing, contours_to_draw, 0, line_color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
    cv::drawContours(drawing, contours_to_draw, 1, line_color);

    return drawing;
}

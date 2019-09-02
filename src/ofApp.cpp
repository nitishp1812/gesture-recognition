#include "ofApp.h"

void ofApp::setup(){
    camera_width_ = 640;
    camera_height_ = 480;

    // Initialize the video stream and the required classifier data
    camera_grabber_.initGrabber(camera_width_, camera_height_);
    categorizer_.Initialize();

    to_draw_ = "";
}

void ofApp::update(){
    camera_grabber_.update();

    // Draw a rectangle on the image from the video stream whenever there is a new frame
    if (camera_grabber_.isFrameNew()) {
        cv::Mat camera_image = ofxCv::toCv(camera_grabber_.getPixels());
        cv::Mat altered_image = DrawBox(camera_image);

        display_image_.clear();
        ofPixels altered_image_pixels;
        ofxCv::toOf(altered_image, altered_image_pixels);

        display_image_.setFromPixels(altered_image_pixels);
    }
}

void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255, 255, 255);

    // Draw the altered camera image
    display_image_.draw(0, 80);

    // Draw the classifier output in a centralized manner
    if (to_draw_ != "") {
        int x_positon = 300 - (to_draw_.length() * 12);

        // if start position is becoming too small, keep it at a minimum
        if (x_positon < 10) {
            x_positon = 10;
        }

        // if text has become too long start deleting from behind
        if ((x_positon + (to_draw_.length() * 12)) > 600) {
            to_draw_ = to_draw_.substr(4);
        }

        //write the label with the given font and at the given position
        display_font_.load("Raleway-Light.ttf", 20);
        display_font_.drawString(to_draw_, x_positon, 650);
    } else {
        display_font_.load("Raleway-Light.ttf", 20);
        display_font_.drawString("Press the space bar to predict from the green box", 15, 650);
    }
}

void ofApp::keyPressed(int key) {
    switch(key) {

        //Classify the data when requested
        case ' ': {
            cv::Mat image_data = ofxCv::toCv(display_image_.getPixels());
            
            // get the image in the required form
            cv::Mat hand_pixels = GetHandPixels(image_data);
            PreprocessImage(hand_pixels);
            cv::Mat contours = GetContours(hand_pixels);

            // get the label for the image
            std::string predicted = categorizer_.Compare(contours);
            to_draw_ += " " + predicted;

            break;
        }

        default:
            to_draw_ = "";
    }
}

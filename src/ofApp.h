#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "image_manipulator.h"
#include "image_categorizer.h"

#include <iostream>

class ofApp : public ofBaseApp{

	// Variable to get the camera image
	ofVideoGrabber camera_grabber_;

	// Variable to store the pixels of the altered camera image
	ofImage display_image_;

	// Variables to store the length and breadth of the camera image
	int camera_width_;
	int camera_height_;

	// Variable to store the necessary classification data
	Categorizer categorizer_;

	// Variable to store the font of the output string
	ofTrueTypeFont display_font_;

	// Variable to store the classified output string
	std::string to_draw_;

  public:
	// Method to setup the fields for classification and the GUI
	void setup();

	//Method to update the camera frame
	void update();

	//Method to draw the camera image and related data
	void draw();

	//Method to get user input for classification
	void keyPressed(int key);
};

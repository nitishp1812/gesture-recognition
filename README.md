# Gesture Recognition

#### I am reconfiguring this project for python and building a neural network for better results.

## Final Project - Translation Engine From Sign Language to English

This application uses a webcam and converts Sign Language to written English.

This application was written in C++ with the msys2 compiler for Windows and Visual Studio Code

## Usage Instructions

- Download openFrameworks from their site and set it up following the instructions for the msys2 compiler
  - After having built the dependencies continue on to the next step
- Clone this repository into the `$(OF_ROOT)/apps/myApps/` folder
- Install OpenCV for the msys2 distribution

After completing all of the above steps, simply run `make` from the msys2 MinGW32/MinGW64 terminal. \\
After the project has built use `make RunRelease` to run the application

## Testing

Tests were written using the _Catch_ library and a makefile within the tests directory \\
To run the tests, `cd` into the tests directory and run `make`. \\
After this, run the `tests.exe` file by running `./tests.exe` from within the directory on the command line

## NOTE

This project has not been configured to run on different environments like Visual Studio, Linux etc.

### Author

Nitish Poddar

#include "image_categorizer.h"

void Categorizer::Initialize() {
    // generate the files with the image filenames for the respective user states
    GenerateFiles();

    LoadImages();
}

std::string Categorizer::Compare(cv::Mat user_image) {
    std::vector<double> differences;

    // Generate the difference in double output for each image with the input image
    for (cv::Mat pre_defined_image : this->images_to_compare_) {
        differences.push_back(this->GetDifference(user_image, pre_defined_image));
    }

    // Get the index with the least difference which is the predicted label
    double min = 1000.0;
    int min_index = -1;

    for (int i = 0; i < differences.size(); ++i) {
        if (differences[i] < min) {
            min_index = i;
            min = differences[i];
        }
    }

    // return the predicted string label
    return this->GetPredicted(min_index);
}

double Categorizer::GetDifference(cv::Mat image_1, cv::Mat image_2) {
    std::vector<cv::Mat> images = {image_1, image_2};

    // calculate the difference in the histograms
    cv::Mat hist_1, hist_2;
    int hist_size = 256;

    float range[] = {0, 256};
    const float* hist_range = {range};

    cv::calcHist(&images[0], 1, 0, cv::Mat(), hist_1, 1, &hist_size, &hist_range);
    cv::calcHist(&images[1], 1, 0, cv::Mat(), hist_2, 1, &hist_size, &hist_range);

    double hist_difference = cv::compareHist(hist_1, hist_2, cv::HISTCMP_BHATTACHARYYA);

    // return the difference between the histograms
    return std::fabs(hist_difference);
}

void Categorizer::GenerateFiles() {
    std::string directory_name = "../gestures";

    // load the file paths and store them to a file to be used when loading the images
    std::ofstream file(kFileName);

    for (int i = 1; i <= 36; ++i) {
        std::string file_path = directory_name + "/" + std::to_string(i) + ".png";

        file << file_path << "\n";
    }
}

void Categorizer::LoadImages() {
    std::ifstream file_reader(kFileName);
    this->images_to_compare_.clear();

    // read all the images to a vector
    while (!file_reader.eof()) {
        std::string image_filename;
        file_reader >> image_filename;

        if (this->images_to_compare_.size() == 36) {
            break;
        }

        this->images_to_compare_.push_back(cv::imread(image_filename, cv::IMREAD_GRAYSCALE));
    }
}

std::string Categorizer::GetPredicted(int label) {
    // load the file with the labels
    std::ifstream conversion_file("data/conversion_code.txt");
    std::string predicted;

    // traverse to the proper line
    for (int i = 0; i < label; ++i) {
        conversion_file >> predicted;
    }
    conversion_file >> predicted;

    return predicted;
}

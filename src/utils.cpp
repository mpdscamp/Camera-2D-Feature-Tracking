#include "utils.hpp"

void printKeypointStatistics(const std::string& detectorType, double avgMinSize, double avgMaxSize, double avgMeanSize, double avgStdDevSize, double avgKeypointsPerImage, double detectorTime) {
    std::string filepath = "../results/keypoint_data.csv";
    std::ifstream inFile(filepath);
    bool fileExists = inFile.good(); // Check if file exists
    bool fileIsEmpty = false;
    if (fileExists) {
        fileIsEmpty = (inFile.peek() == std::ifstream::traits_type::eof()); // Check if file is empty
    }
    inFile.close();

    std::ofstream outputFile(filepath, std::ios_base::app);
    if (!fileExists || fileIsEmpty) {
        // Write header if file doesn't exist or is empty
        outputFile << "Detector Type, Average Min Size, Average Max Size, Average Mean Size, Average StdDev Size, Average Keypoints Per Image, Time Taken (ms)\n";
    }

    outputFile << detectorType << "," 
            << avgMinSize << "," 
            << avgMaxSize << "," 
            << avgMeanSize << "," 
            << avgStdDevSize << ","
            << avgKeypointsPerImage << ","
            << detectorTime * 1000.0f << "\n";

    outputFile.close();
}

void printMatchStatistics(const std::string& detectorType, const std::string& descriptorType, double avgMatches, double avgMatchPercentage, double detectorTime, double descriptorTime) {
    std::string filepath = "../results/match_data.csv";
    std::ifstream inFile(filepath);
    bool fileExists = inFile.good(); // Check if file exists
    bool fileIsEmpty = false;
    if (fileExists) {
        fileIsEmpty = (inFile.peek() == std::ifstream::traits_type::eof()); // Check if file is empty
    }
    inFile.close();

    std::ofstream outputFile(filepath, std::ios_base::app);
    if (!fileExists || fileIsEmpty) {
        // Write header if file doesn't exist or is empty
        outputFile << "Detector Type, Descriptor Type, Average Matches, Average Match Percentage, Detector Time (ms), Descriptor Time (ms)\n";
    }

    outputFile << detectorType << "," 
            << descriptorType << "," 
            << avgMatches << "," 
            << avgMatchPercentage << ","
            << detectorTime * 1000.0f << ","
            << descriptorTime * 1000.0f << "\n";
            
    outputFile.close();
}
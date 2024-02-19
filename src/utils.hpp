#ifndef utils_hpp
#define utils_hpp

#include <fstream>
#include <iostream>

void printKeypointStatistics(const std::string& detectorType, double avgMinSize, double avgMaxSize, double avgMeanSize, double avgStdDevSize, double avgKeypointsPerImage, double detectorTime);
void printMatchStatistics(const std::string& detectorType, const std::string& descriptorType, double avgMatches, double avgMatchPercentage, double detectorTime, double descriptorTIme);

#endif /* utils_hpp */
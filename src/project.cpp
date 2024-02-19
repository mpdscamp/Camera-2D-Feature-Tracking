/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"
#include "utils.hpp"

using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{

    /* INIT VARIABLES AND DATA STRUCTURES */

    // data location
    string dataPath = "../";

    // camera
    string imgBasePath = dataPath + "images/";
    string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
    string imgFileType = ".png";
    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
    int imgEndIndex = 9;   // last file index to load
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

    // misc
    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
    vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
    bool bVis = false;            // visualize results
    std::vector<string> detectorList = {"SHITOMASI", "HARRIS", "FAST", "BRISK", "ORB", "AKAZE", "SIFT"};
    string detectorType = detectorList[0]; // 0 - SHITOMASI, 1 - HARRIS, 2 - FAST, 3 - BRISK, 4 - ORB, 5 - AKAZE, 6 - SIFT
    std::vector<string> descriptorList = {"BRISK", "BRIEF", "ORB", "FREAK", "AKAZE", "SIFT"};
    string descriptorType = descriptorList[0]; // 0 - BRISK, 1 - BRIEF, 2 - ORB, 3 - FREAK, 4 - AKAZE, 5 - SIFT
    
    /* MAIN LOOP OVER ALL IMAGES */

    // Define statistics measurements
    double totalMinSize = 0, totalMaxSize = 0, totalSumSize = 0, totalVarianceSum = 0;
    int totalKeypoints = 0;
    double detectorTime = 0.0f; // Time measurement
    double descriptorTime = 0.0f; // Time measurement
    double avgMatches = 0.0f; // Total matches

    for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
    {
        /* LOAD IMAGE INTO BUFFER */

        // assemble filenames for current index
        ostringstream imgNumber;
        imgNumber << setfill('0') << setw(imgFillWidth) << imgStartIndex + imgIndex;
        string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

        // load image from file and convert to grayscale
        cv::Mat img, imgGray;
        img = cv::imread(imgFullFilename);
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

        //// STUDENT ASSIGNMENT
        //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

        // push image into data frame buffer
        if (dataBuffer.size() >= dataBufferSize)
        {
            dataBuffer.erase(dataBuffer.begin());
        }
        DataFrame frame;
        frame.cameraImg = imgGray;
        dataBuffer.push_back(frame);

        //// EOF STUDENT ASSIGNMENT
        cout << "#1 : LOAD IMAGE INTO BUFFER done" << endl;

        /* DETECT IMAGE KEYPOINTS */

        // extract 2D keypoints from current image
        vector<cv::KeyPoint> keypoints; // create empty feature list for current image
        

        //// STUDENT ASSIGNMENT
        //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
        //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
        if (detectorType.compare("SHITOMASI") == 0)
        {
            double tempDetectorTime = (double)cv::getTickCount();
            detKeypointsShiTomasi(keypoints, imgGray, false);
            tempDetectorTime = ((double)cv::getTickCount() - tempDetectorTime) / cv::getTickFrequency();

            detectorTime += tempDetectorTime;
        }
        else if (detectorType.compare("HARRIS") == 0)
        {
            double tempDetectorTime = (double)cv::getTickCount();
            detKeypointsHarris(keypoints, imgGray, false);
            tempDetectorTime = ((double)cv::getTickCount() - tempDetectorTime) / cv::getTickFrequency();

            detectorTime += tempDetectorTime;
        }
        else if (detectorType.compare("FAST") == 0)
        {
            double tempDetectorTime = (double)cv::getTickCount();
            detKeypointsFast(keypoints, imgGray, false);
            tempDetectorTime = ((double)cv::getTickCount() - tempDetectorTime) / cv::getTickFrequency();

            detectorTime += tempDetectorTime;
        }
        else if (detectorType.compare("BRISK") == 0)
        {
            double tempDetectorTime = (double)cv::getTickCount();
            detKeypointsBrisk(keypoints, imgGray, false);
            tempDetectorTime = ((double)cv::getTickCount() - tempDetectorTime) / cv::getTickFrequency();

            detectorTime += tempDetectorTime;
        }
        else if (detectorType.compare("ORB") == 0)
        {
            double tempDetectorTime = (double)cv::getTickCount();
            detKeypointsOrb(keypoints, imgGray, false);
            tempDetectorTime = ((double)cv::getTickCount() - tempDetectorTime) / cv::getTickFrequency();

            detectorTime += tempDetectorTime;
        }
        else if (detectorType.compare("AKAZE") == 0)
        {
            double tempDetectorTime = (double)cv::getTickCount();
            detKeypointsAkaze(keypoints, imgGray, false);
            tempDetectorTime = ((double)cv::getTickCount() - tempDetectorTime) / cv::getTickFrequency();

            detectorTime += tempDetectorTime;
        }
        else if (detectorType.compare("SIFT") == 0)
        {
            double tempDetectorTime = (double)cv::getTickCount();
            detKeypointsSift(keypoints, imgGray, false);
            tempDetectorTime = ((double)cv::getTickCount() - tempDetectorTime) / cv::getTickFrequency();

            detectorTime += tempDetectorTime;
        }
        else
        {
            throw std::runtime_error("Unsupported detector type: " + detectorType);
        }
        //// EOF STUDENT ASSIGNMENT

        //// STUDENT ASSIGNMENT
        //// TASK MP.3 -> only keep keypoints on the preceding vehicle

        // only keep keypoints on the preceding vehicle
        bool bFocusOnVehicle = true;
        cv::Rect vehicleRect(535, 180, 180, 150);
        if (bFocusOnVehicle)
        {
            for (auto it = keypoints.begin(); it != keypoints.end();)
            {
                if (!vehicleRect.contains(it->pt))
                {
                    it = keypoints.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        // Statistics calculations
        double minSize = std::numeric_limits<double>::max(), maxSize = 0, sumSize = 0;
        for (const auto& kp : keypoints) {
            double kpSize = kp.size;
            minSize = std::min(minSize, kpSize);
            maxSize = std::max(maxSize, kpSize);
            sumSize += kpSize;
        }
        double meanSize = keypoints.empty() ? 0 : sumSize / keypoints.size();

        double varianceSum = 0;
        for (const auto& kp : keypoints) {
            varianceSum += std::pow(kp.size - meanSize, 2);
        }
        double stdDevSize = keypoints.empty() ? 0 : std::sqrt(varianceSum / keypoints.size());

        // Update accumulators
        totalMinSize += minSize;
        totalMaxSize += maxSize;
        totalSumSize += sumSize;
        totalVarianceSum += varianceSum;
        totalKeypoints += keypoints.size();

        //// EOF STUDENT ASSIGNMENT

        // optional : limit number of keypoints (helpful for debugging and learning)
        bool bLimitKpts = false;
        if (bLimitKpts)
        {
            int maxKeypoints = 50;

            if (detectorType.compare("SHITOMASI") == 0)
            { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
            }
            cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
            cout << " NOTE: Keypoints have been limited!" << endl;
        }

        // push keypoints and descriptor for current frame to end of data buffer
        (dataBuffer.end() - 1)->keypoints = keypoints;
        cout << "#2 : DETECT KEYPOINTS done" << endl;

        /* EXTRACT KEYPOINT DESCRIPTORS */

        //// STUDENT ASSIGNMENT
        //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
        //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

        cv::Mat descriptors;
        double t = (double)cv::getTickCount();
        descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType);
        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
        descriptorTime += t;
        //// EOF STUDENT ASSIGNMENT

        // push descriptors for current frame to end of data buffer
        (dataBuffer.end() - 1)->descriptors = descriptors;

        cout << "#3 : EXTRACT DESCRIPTORS done" << endl;

        if (dataBuffer.size() > 1) // wait until at least two images have been processed
        {

            /* MATCH KEYPOINT DESCRIPTORS */

            vector<cv::DMatch> matches;
            string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN
            string descriptorType = "DES_BINARY"; // DES_BINARY, DES_HOG
            string selectorType = "SEL_KNN";       // SEL_NN, SEL_KNN

            //// STUDENT ASSIGNMENT
            //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
            //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp

            matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                             (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                             matches, descriptorType, matcherType, selectorType);

            //// EOF STUDENT ASSIGNMENT

            // store matches in current data frame
            (dataBuffer.end() - 1)->kptMatches = matches;
            avgMatches += matches.size();

            cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << endl;

            // visualize matches between current and previous image
            bVis = true;
            if (bVis)
            {
                cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                matches, matchImg,
                                cv::Scalar::all(-1), cv::Scalar::all(-1),
                                vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                string windowName = "Matching keypoints between two camera images";
                cv::namedWindow(windowName, 7);
                cv::imshow(windowName, matchImg);
                cout << "Press key to continue to next image" << endl;
                cv::waitKey(0); // wait for key to be pressed
            }
            bVis = false;
        }

    } // eof loop over all images

    // Calculate keypoint statistics
    double avgMinSize = totalMinSize / (imgEndIndex - imgStartIndex + 1);
    double avgMaxSize = totalMaxSize / (imgEndIndex - imgStartIndex + 1);
    double avgMeanSize = totalSumSize / (totalKeypoints ? totalKeypoints : 1);
    double avgStdDevSize = std::sqrt(totalVarianceSum / (totalKeypoints ? totalKeypoints : 1));
    double avgKeypointsPerImage = static_cast<double>(totalKeypoints) / (imgEndIndex - imgStartIndex + 1);
    detectorTime /= (imgEndIndex - imgStartIndex + 1);
    descriptorTime /= (imgEndIndex - imgStartIndex + 1);

    // Calculate match statistics
    double avgMatchPercentage = avgMatches / totalKeypoints * 100.0f;
    avgMatches /= (imgEndIndex - imgStartIndex + 1);

    // Write keypoint-detector statistics to a file
    printKeypointStatistics(detectorType, avgMinSize, avgMaxSize, avgMeanSize, avgStdDevSize, avgKeypointsPerImage, detectorTime);

    // Write keypoint matches statistics to a file
    printMatchStatistics(detectorType, descriptorType, avgMatches, avgMatchPercentage, detectorTime, descriptorTime);

    return 0;
}
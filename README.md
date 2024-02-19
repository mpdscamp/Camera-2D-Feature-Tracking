# Camera 2D Feature Tracking

This project implements keypoint detectors, descriptors, and methods to match them between successive images. It tracks features from a vehicle-mounted camera for use in tasks like localization, mapping, and object recognition.

## Dependencies for Running Locally
* cmake >= 3.14
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
* OpenCV >= 4.1
* gcc/g++ >= 8.0

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./2D_feature_tracking`.

## Rubric Points
### Data Buffer Optimization
We successfully implemented a ring buffer to hold the last N (N = 2) images and reuse them within the data pipeline.

### Keypoint detection
We have implemented detectors such as SHITOMASI, HARRIS, FAST, BRISK, ORB, AKAZE, and SIFT which can be selected by setting a string accordingly.

### Keypoint Removal
We removed all keypoints outside of a pre-defined rectangle, that encompasses the target car, and only used the keypoints within the rectangle for further processing.

### Descriptors
Descriptors BRISK, BRIEF, ORB, FREAK, AKAZE, and SIFT have been implemented and made selectable by setting a string accordingly.

### FLANN Matching and k-Nearest Neighbor Selection
FLANN matching and k-nearest neighbor selection were implemented and can be selected using the respective strings in the main function.

### Descriptor Distance Ratio
K-Nearest-Neighbor matching is used to implement the descriptor distance ratio test, which looks at the ratio of best vs. second-best match to decide whether to keep an associated pair of keypoints.

## Results
The results of the implementation are located in "results/keypoint_data.csv", for statistcs related to keypoint detection, and "results/match_data.csv", for statistics related to keypoint-descriptor matches.

The top 3 detector/descriptor combinations as per the performance evaluation, considering the number of keypoints detected, number of matches and time taken, are:

1. FAST + BRIEF
2. AKAZE + BRIEF
3. FAST + ORB

## Conclusion
This project successfully implements the necessary components for 2D feature tracking. It provides flexibility in choosing different detectors and descriptors and evaluates their performance in terms of speed and matching accuracy. The best-performing combinations are recommended based on the application's needs for real-time processing and reliable feature matching.

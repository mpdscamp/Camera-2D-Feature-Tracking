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
Implement a ring buffer to hold the last N images and reuse them within the data pipeline.

### Keypoints
We have implemented detectors such as HARRIS, FAST, BRISK, ORB, AKAZE, and SIFT which can be selected by setting a string accordingly.

### Keypoint Removal
Remove all keypoints outside of a pre-defined rectangle and only use the keypoints within the rectangle for further processing.

### Descriptors
Descriptors BRIEF, ORB, FREAK, AKAZE, and SIFT have been implemented and made selectable by setting a string accordingly.

### FLANN Matching and k-Nearest Neighbor Selection
FLANN matching and k-nearest neighbor selection are implemented and can be selected using the respective strings in the main function.

### Descriptor Distance Ratio
K-Nearest-Neighbor matching is used to implement the descriptor distance ratio test, which looks at the ratio of best vs. second-best match to decide whether to keep an associated pair of keypoints.

### Performance Evaluation 1
Count the number of keypoints on the preceding vehicle for all 10 images and take note of the distribution of their neighborhood size.

### Performance Evaluation 2
Count the number of matched keypoints for all 10 images using all possible combinations of detectors and descriptors.

### Performance Evaluation 3
Log the time it takes for keypoint detection and descriptor extraction. The results must be entered into a spreadsheet and based on this data, the TOP3 detector / descriptor combinations must be recommended as the best choice for our purpose of detecting keypoints on vehicles.

## Results
The results of the implementation are as follows:

* Number of Keypoints Detected:
  * SHITOMASI: ...
  * ...

* Keypoint Matching:
  * Matches using FAST detector and BRIEF descriptor: ...
  * ...

* Timing Analysis:
  * SHITOMASI detection took on average: ...
  * ...

The top 3 detector/descriptor combinations as per the performance evaluation are:

1. ...
2. ...
3. ...

For more detailed analysis and results, please refer to the project report available in this repository.

## Conclusion
This project successfully implements the necessary components for 2D feature tracking. It provides flexibility in choosing different detectors and descriptors and evaluates their performance in terms of speed and matching accuracy. The best-performing combinations are recommended based on the application's needs for real-time processing and reliable feature matching.

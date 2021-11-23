# ImageToBag
Modified from https://github.com/keenan-burnett/BagFromImages.git
Originally from https://github.com/raulmur/BagFromImages.git

ROS package to generate a rosbag from a collection of images. The filenames of the images are the timestamps of each of the image. TODO: *And later on will developed a version that supports the alpabetically ordered images under a fixed frequency.*

The bag will publish the images to topic `/image_seg/compressed`. TODO:*can be set in the launch file.*

Tested in ROS Melodic + OpenCV 3.2.0 + C++ 11

## Installation

    mkdir -p /catkin_ws/src
    cd /catkin/src
    git clone https://github.com/Jarvis-sustech/ImageToRosbag.git
    cd ..
    catkin build

## Usage:

    rosrun BagFromImages main [PATH_OF_FOLDER_IMAGES] [EXT._OF_IMAGE] [PATH_TO_OUPUT_BAG]
  
 - `PATH_OF_FOLDER_IMAGES`: Path to folder that contains image sequences.
 - `EXT._OF_IMAGE`: eg. ".png", ".jpg".
 - `PATH_TO_OUTPUT_BAG`: Path to save the bag (including the filename e.g. directory/filename.bag)

## Notes:

    
    set(OpenCV_DIR /usr/share/OpenCV)
- Be sure to set the correct path of the OPENCV of your installation at the CMakeLists.txt

Also, in this package, we use the cv_brigde to compressed image, therefore save the space for a RosBag.




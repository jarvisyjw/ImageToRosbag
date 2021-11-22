#include<iostream>
#include<ros/ros.h>
#include<rosbag/bag.h>
#include<rosbag/view.h>
#include<sensor_msgs/Image.h>
#include<std_msgs/Time.h>
#include<std_msgs/Header.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <cstdlib> 


#include "Thirdparty/DLib/FileFunctions.h"
#include <fstream>


using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "BagFromImages");

    if(argc!=4)
    {
        cerr << "Usage: rosrun BagFromImages BagFromImages <path image folder> <extension eg. (.png)> <path to output bag>" << endl;
        return 0;
    }

    ros::start();
    // read in the image
    vector<string> filenames =
            DUtils::FileFunctions::Dir(argv[1], argv[2], true);
    // print out image info
    cout << "num of images: " << filenames.size() << endl;
    cout << "start image @" << filenames[0] << endl;
    cout << "end image @" << filenames[filenames.size()] <<endl;
    
    std::string filename; 
    
    // Frequency TODO:
    //double freq = atof(argv[2]);

    // Output bag
    rosbag::Bag bag_out(argv[3],rosbag::bagmode::Write);
    
    // const float T=1.0f/freq;
    // ros::Duration d(T);

    for(size_t i=0;i<filenames.size();i++)
    {
        if(!ros::ok())
            break;
        //cv read in image
        cv::Mat im = cv::imread(filenames[i],CV_LOAD_IMAGE_COLOR);
        // extract image name as timestamp
        filename = DUtils::FileFunctions::FileName(filenames[i],argv[2]);
        char* end;
        long double t = strtold(filename.c_str(),&end);
        // timestamp read in as seconds
        ros::Time stamp = ros::Time().fromSec(t);
        cout<< "time stamp in secs: " << stamp.toSec() << endl;
        // create cv_bridge object
        cv_bridge::CvImage cvImage;
        cvImage.image = im;
        cvImage.encoding = sensor_msgs::image_encodings::RGB8;
        cvImage.header.stamp = stamp;
        //write the bag
        //use toCompressedImageMsg to save the storage space
        bag_out.write("/image_seg/compressed",ros::Time(stamp),cvImage.toCompressedImageMsg());
        //t+=d;
        //output the process percentage
        cout << "processing @: " << i <<  "/" << filenames.size() << endl;
    }

    bag_out.close();
    ros::shutdown();
    return 0;
}

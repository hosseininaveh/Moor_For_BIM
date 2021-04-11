#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>
#include <iostream>


using namespace std;
int readImageCount = 0;
int t=0;
string ST;
string countern;
string resultDir="/home/ali/Desktop/";
bool captured_image=0;
void chatterCallback5(const std_msgs::String::ConstPtr& msg)
{
  if (msg->data =="p")
    captured_image=1;
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  if (captured_image==1)
  {
    ostringstream convert;
    convert << t;
    ST = convert.str();
    if (t<10)
      countern="000";
    else if (t<100 && t>=10)
      countern="00";
    else if (t<1000 && t>=100)
      countern="0";
    else if (t<10000 && t>=1000)
      countern="";
    string filename2 = resultDir + countern + ST + ".jpg";

    ROS_INFO("image is saved");
    cv::imwrite(filename2, cv_bridge::toCvShare(msg, "bgr8")->image);
    captured_image=0;
    t=t+1;
  }

 
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_grabber");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  ros::Subscriber sub2 = nh.subscribe("/IfCapture", 1, chatterCallback5);
  image_transport::Subscriber sub = it.subscribe("/DSLR/image_raw", 1, imageCallback);
  ros::spin();
  return 0;
}

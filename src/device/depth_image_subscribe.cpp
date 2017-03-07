#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    cv::imshow("view", cv_bridge::toCvShare(msg, "16UC1")->image);
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to '16UC1'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "depth_image_viewer_cpp");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::startWindowThread();
//  image_transport::ImageTransport it(nh);
//  image_transport::Subscriber sub = it.subscribe("/camera/image", 1, imageCallback);
  ros::Subscriber sub = nh.subscribe("/camera/depth/image_raw", 1000, imageCallback);
  ros::spin();
  cv::destroyWindow("view");
}

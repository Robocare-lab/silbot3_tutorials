#include "ros/ros.h"
#include "silbot3_msgs/Device_Gyro_Msg.h"

void callback(const silbot3_msgs::Device_Gyro_Msg::ConstPtr& msg)
{
  ROS_INFO("angle : %f, rate : %f", msg->angle, msg->rate);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gyro_listener_cpp");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/DeviceNode/Gyro/data", 1000, callback);

  ros::spin();

  return 0;
}

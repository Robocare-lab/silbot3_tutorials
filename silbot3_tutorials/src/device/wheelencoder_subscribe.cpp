#include "ros/ros.h"
#include "silbot3_msgs/Device_WheelEncoder_Msg.h"

void callback(const silbot3_msgs::Device_WheelEncoder_Msg::ConstPtr& msg)
{
  ROS_INFO("x : %d, y : %d, theta : %d", msg->x, msg->y,msg->t);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheelencoder_listener_cpp");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/DeviceNode/WheelEncoder/data", 1000, callback);

  ros::spin();

  return 0;
}

#include "ros/ros.h"
#include "silbot3_msgs/Device_Touch_Msg.h"

void callback(const silbot3_msgs::Device_Touch_Msg::ConstPtr& msg)
{
  ROS_INFO("touch button data : %d %d %d %d", msg->param[0], msg->param[1],msg->param[2],msg->param[3]);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "touch_listener_cpp");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/DeviceNode/TouchButton/data", 1000, callback);

  ros::spin();

  return 0;
}

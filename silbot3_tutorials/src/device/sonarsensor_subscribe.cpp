#include "ros/ros.h"
#include "silbot3_msgs/Device_Ultra_Msg.h"

void callback(const silbot3_msgs::Device_Ultra_Msg::ConstPtr& msg)
{
  ROS_INFO("sonar data : %3d %3d %3d %3d %3d %3d %3d %3d", msg->param[0],msg->param[1],msg->param[2],msg->param[3],msg->param[4],msg->param[5],msg->param[6],msg->param[7]);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sonar_listener_cpp");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/DeviceNode/UltraSonic/data", 1000, callback);

  ros::spin();

  return 0;
}

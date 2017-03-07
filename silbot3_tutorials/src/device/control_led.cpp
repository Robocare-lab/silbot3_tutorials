#include "ros/ros.h"
#include "silbot3_msgs/Device_LED_Msg.h"

ros::Publisher publisher;

void on(int r, int g, int b)
{
  silbot3_msgs::Device_LED_Msg msg;
  msg.command = "on";
  msg.id = 0xF5;
  msg.bright = 1;
  msg.red = r;
  msg.green = g;
  msg.blue = b;
  publisher.publish(msg);
  ROS_INFO("published");
}

void controlLed() {
  on(1,1,1);
  ros::Duration(1).sleep();
  on(1,0,0);
  ros::Duration(1).sleep();
  on(0,1,0);
  ros::Duration(1).sleep();
  on(0,0,1);
  ros::Duration(1).sleep();
  on(0,0,0);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "control_led_cpp");
  ros::NodeHandle n;
  publisher = n.advertise<silbot3_msgs::Device_LED_Msg>("/DeviceNode/LED/commands", 1000);

  int count = 0;
  while (count < 0) {
    count = publisher.getNumSubscribers();
    ROS_INFO("wait device led subscriber...");
    ros::Duration(0.1).sleep();
  }
  ROS_INFO("found device led subscriber...");
  ros::Duration(0.5).sleep();
  controlLed();

  return 0;
}

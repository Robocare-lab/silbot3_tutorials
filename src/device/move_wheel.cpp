#include "ros/ros.h"
#include "silbot3_msgs/Device_Wheel_Msg.h"

#define COMMAND_WHEEL_ON                                "WHEEL_ON"
#define COMMAND_WHEEL_OFF                               "WHEEL_OFF"
#define COMMAND_WHEEL_STOP                              "WHEEL_STOP"
#define COMMAND_WHEEL_MOVE_BY_TR_VELOCITY               "WHEEL_MOVE_BY_TR_VELOCITY"
#define COMMAND_WHEEL_MOVE_BY_WHEEL_VELOCITY            "WHEEL_MOVE_BY_WHEEL_VELOCITY"
#define COMMAND_WHEEL_MOVE_TO_DELTA_X                   "WHEEL_MOVE_TO_DELTA_X"
#define COMMAND_WHEEL_MOVE_TO_DELTA_THETA               "WHEEL_MOVE_TO_DELTA_THETA"
#define COMMAND_WHEEL_MOVE_TO_DELTA_XYTHETA             "WHEEL_MOVE_TO_DELTA_XYTHETA"
#define COMMAND_WHEEL_MOVE_BY_VELOCITY_XYT              "WHEEL_MOVE_BY_VELOCITY_XYT"
#define COMMAND_WHEEL_EMERGENCY_STOP                    "WHEEL_EMERGENCY_STOP"
#define COMMAND_WHEEL_EMERGENCY_RELEASE                 "WHEEL_EMERGENCY_RELEASE"
#define COMMAND_WHEEL_RESET                             "WHEEL_EMERGENCY_RESET"
#define COMMAND_WHEEL_EMERGENCY_MOVE_BY_VELOCITY_XYT    "WHEEL_EMERGENCY_MOVE_BY_VELOCITY_XYT"
#define COMMAND_WHEEL_SELF_DIAGNOSIS                    "WHEEL_SELF_DIAGNOSIS"
#define COMMAND_WHEEL_START_AUTO_CHARGE                 "WHEEL_START_AUTO_CHARGE"
#define COMMAND_WHEEL_STOP_AUTO_CHARGE                  "WHEEL_STOP_AUTO_CHARGE"


ros::Publisher publisher;

void moveWheel()
{
  double xvel = 200; // 100 mm / sec
  double yvel = 200; // mm / sec
  double theta = 30; // degree / sec

  silbot3_msgs::Device_Wheel_Msg msg1;
  msg1.command = "WHEEL_MOVE_BY_VELOCITY_XYT";
  msg1.dParams.push_back(xvel);
  msg1.dParams.push_back(yvel);
  msg1.dParams.push_back(theta);
  publisher.publish(msg1);

  ros::Duration(2).sleep();

  silbot3_msgs::Device_Wheel_Msg msg2;
  msg2.command = "WHEEL_MOVE_BY_VELOCITY_XYT";
  msg2.dParams.push_back(-xvel);
  msg2.dParams.push_back(-yvel);
  msg2.dParams.push_back(-theta);
  publisher.publish(msg2);

  ros::Duration(2).sleep();

  silbot3_msgs::Device_Wheel_Msg msg3;
  msg3.command = "WHEEL_MOVE_BY_VELOCITY_XYT";
  msg3.dParams.push_back(0);
  msg3.dParams.push_back(0);
  msg3.dParams.push_back(0);
  publisher.publish(msg3);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_wheel_cpp");
  ros::NodeHandle n;
  publisher = n.advertise<silbot3_msgs::Device_Wheel_Msg>("/DeviceNode/Wheel/commands", 1000);

  int count = 0;
  while (count < 0) {
    count = publisher.getNumSubscribers();
    ROS_INFO("wait device wheel subscriber...");
    ros::Duration(0.1).sleep();
  }
  ROS_INFO("found device wheel subscriber...");
  ros::Duration(0.5).sleep();
  moveWheel();

  return 0;
}

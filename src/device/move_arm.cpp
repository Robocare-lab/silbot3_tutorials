#include "ros/ros.h"
#include "silbot3_msgs/Device_Arm_Msg.h"

#define COMMAND_ARM_ON                                  "ARM_ON"
#define COMMAND_ARM_OFF                                 "ARM_OFF"
#define COMMAND_ARM_STOP                                    "ARM_STOP"
#define COMMAND_ARM_MOVE_TO_HOME                        "ARM_MOVE_TO_HOME"
#define COMMAND_ARM_MOVE_TO_POSITION_ALL                "ARM_MOVE_TO_POSITION_ALL"
#define COMMAND_ARM_MOVE_TO_POSITION_WITH_AXIS_SPEED    "ARM_MOVE_TO_POSITION_WITH_AXIS_SPEED"
#define COMMAND_ARM_MOVE_TO_POSITION_ALL_BOTH           "ARM_MOVE_TO_POSITION_ALL_BOTH"
#define COMMAND_ARM_MOVE_TO_POSITION_ALL_BOTH_WITH_AXIS_SPEED   "ARM_MOVE_TO_POSITION_ALL_BOTH_WITH_AXIS_SPEED"
#define COMMAND_ARM_GET_POSITION                        "ARM_GET_POSITION"
#define COMMAND_ARM_SET_HOME_POSITION                   "ARM_SET_HOME_POSITION"
#define COMMAND_ARM_EMERGENCY_STOP                      "ARM_EMERGENCY_STOP"
#define COMMAND_ARM_EMERGENCY_RELEASE                   "ARM_EMERGENCY_RELEASE"
#define COMMAND_ARM_DETECTING_ERROR                     "ARM_DETECTING_ERROR"
#define COMMAND_ARM_RELEASE_TORQUE                      "ARM_RELEASE_TORQUE"
#define COMMAND_ARM_START_TEACHING                      "ARM_START_TEACHING"
#define COMMAND_ARM_STOP_TEACHING                       "ARM_STOP_TEACHING"


ros::Publisher publisher;

void moveToHome(int armId) {
  silbot3_msgs::Device_Arm_Msg msg;
  msg.command = "ARM_MOVE_TO_HOME";
  msg.motorID.push_back(armId);
  publisher.publish(msg);
}

void moveToPositionAll(int armId, int angles[3], int speed ) {
  silbot3_msgs::Device_Arm_Msg msg;
  msg.command = "ARM_MOVE_TO_POSITION_ALL";
  msg.motorID.push_back(armId);
  msg.angles.push_back(angles[0]);
  msg.angles.push_back(angles[1]);
  msg.angles.push_back(angles[2]);
  msg.speeds.push_back(speed);
  publisher.publish(msg);
}

void moveBothArm(int angles[6], int speed) {
  silbot3_msgs::Device_Arm_Msg msg;
  msg.command = "ARM_MOVE_TO_POSITION_ALL_BOTH";
  msg.speeds.push_back(speed);
  msg.angles.push_back(angles[0]);
  msg.angles.push_back(angles[1]);
  msg.angles.push_back(angles[2]);
  msg.angles.push_back(angles[3]);
  msg.angles.push_back(angles[4]);
  msg.angles.push_back(angles[5]);
  publisher.publish(msg);
}

void moveArm()
{
  // left arm movement
  int speed = 30;
  int angles0[3] = {0,0,0};
  int angles1[3] = {30, 20, -20};
  moveToPositionAll(0, angles1, speed);
  ros::Duration(2).sleep();
  moveToPositionAll(0, angles0, speed);

  ros::Duration(2).sleep();

  // both arm moving
  speed = 60;
  int angles2[6] = {0,0,0,0,0,0};
  int angles3[6] = {120, 20, -20, 120, 20, -20};
  moveBothArm(angles3, speed);
  ros::Duration(2).sleep();
  moveBothArm(angles2, speed);

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_arm_cpp");
  ros::NodeHandle n;
  publisher = n.advertise<silbot3_msgs::Device_Arm_Msg>("/DeviceNode/Arm/commands", 1000);

  int count = 0;
  while (count < 0) {
    count = publisher.getNumSubscribers();
    ROS_INFO("wait device arm subscriber...");
    ros::Duration(0.1).sleep();
  }
  ROS_INFO("found device arm subscriber...");
  ros::Duration(0.5).sleep();
  moveArm();

  return 0;
}

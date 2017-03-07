#include "ros/ros.h"
#include "silbot3_msgs/Device_ErobotPantilt_Msg.h"

/*
string command
int32[] motorID
float64[] angles
int32[] speeds
*/

#define COMMAND_PANTILT_ON                              "PANTILT_ON"
#define COMMAND_PANTILT_OFF                             "PANTILT_OFF"
#define COMMAND_PANTILT_STOP                            "PANTILT_STOP"
#define COMMAND_PANTILT_MOVE_TO_HOME                    "PANTILT_MOVE_TO_HOME "
#define COMMAND_PANTILT_MOVE_TO_RELATIVE_POSITION       "PANTILT_MOVE_TO_RELATIVE_POSITION"
#define COMMAND_PANTILT_MOVE2MOTOR_SYNC                 "PANTILT_MOVE2MOTOR_SYNC"
#define COMMAND_PANTILT_MOVE_MOTOR                      "PANTILT_MOVE_MOTOR"
#define COMMAND_PANTILT_MOVE_ABSOLUTE_POSITION          "PANTILT_MOVE_ABSOLUTE_POSITION"
#define COMMAND_PANTILT_MOVE_ABSOLUTE_POSITION_WITH_SPEED           "PANTILT_MOVE_ABSOLUTE_POSITION_WITH_SPEED"
#define COMMAND_PANTILT_MOVE_ABSOLUTE_POSITION_ALL      "PANTILT_MOVE_ABSOLUTE_POSITION_ALL"
#define COMMAND_PANTILT_GETPOSITION                     "PANTILT_GETPOSITION"
#define COMMAND_PANTILT_SET_COMPLIANCE                  "PANTILT_SET_COMPLIANCE"
#define COMMAND_PANTILT_MOVE_XTION_TILT                 "PANTILT_MOVE_XTION_TILT"
#define COMMAND_PANTILT_GET_XTION_ANGLE                 "PANTILT_GET_XTION_ANGLE"
#define COMMAND_PANTILT_EMERGENCY_STOP                  "PANTILT_EMERGENCY_STOP"
#define COMMAND_PANTILT_EMERGENCY_RELEASE               "PANTILT_EMERGENCY_RELEASE"
#define COMMAND_PANTILT_DETECTING_ERROR                 "PANTILT_DETECTING_ERROR"
#define COMMAND_PANTILT_RELEASE_TORQUE                      "PANTILT_RELEASE_TORQUE"
#define COMMAND_PANTILT_START_TEACHING                      "PANTILT_START_TEACHING"
#define COMMAND_PANTILT_STOP_TEACHING                       "PANTILT_STOP_TEACHING"

ros::Publisher publisher;

void moveToHome(int speed) {
  silbot3_msgs::Device_ErobotPantilt_Msg msg;
  msg.command = "PANTILT_MOVE_TO_HOME";
  msg.speeds.push_back(speed);
  publisher.publish(msg);
}

void moveApsolutePosition(double degLR, double degUD, int speed) {
  silbot3_msgs::Device_ErobotPantilt_Msg msg;
  msg.command = "PANTILT_MOVE_ABSOLUTE_POSITION";
  msg.speeds.push_back(speed);
  msg.angles.push_back(degLR);
  msg.angles.push_back(degUD);
  publisher.publish(msg);
}

void moveHead()
{
  // move head
  moveApsolutePosition(90, 0, 30);
  ros::Duration(3).sleep();
  moveApsolutePosition(-90, 0, 30);
  ros::Duration(6).sleep();
  moveApsolutePosition(0, 0, 30);
  ros::Duration(3).sleep();
  moveApsolutePosition(20, 20, 20);
  ros::Duration(1).sleep();
  moveApsolutePosition(0, 40, 40);
  ros::Duration(1).sleep();
  moveApsolutePosition(0, 0, 40);
  ros::Duration(1).sleep();
  moveApsolutePosition(20, 20, 20);
  ros::Duration(1).sleep();
  moveApsolutePosition(0, 0, 20);
  ros::Duration(1).sleep();

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_head_cpp");
  ros::NodeHandle n;
  publisher = n.advertise<silbot3_msgs::Device_ErobotPantilt_Msg>("/DeviceNode/Pantilt/commands", 1000);

  int count = 0;
  while (count < 0) {
    count = publisher.getNumSubscribers();
    ROS_INFO("wait device head subscriber...");
    ros::Duration(0.1).sleep();
  }
  ROS_INFO("found device head subscriber...");
  ros::Duration(0.5).sleep();
  moveHead();

  return 0;
}

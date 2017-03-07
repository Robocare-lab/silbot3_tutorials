#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import Device_Arm_Msg
'''
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
'''

class Arm :
    def __init__(self):
        self.publisher = rospy.Publisher('/DeviceNode/Arm/commands', Device_Arm_Msg, queue_size=10)
        while self.publisher.get_num_connections() < 1 :
            rospy.loginfo("wait device arm subscriber...")
            rospy.sleep(0.1)
        rospy.loginfo("found device arm subscriber...")

    def moveToHome(self, armId):
        msg = Device_Arm_Msg()
        msg.command = "ARM_MOVE_TO_HOME"
        msg.motorID.append(armId)
        self.publisher.publish(msg)

    def moveToPositionAll(self, armId, angles, speed):
        msg = Device_Arm_Msg()
        msg.command = "ARM_MOVE_TO_POSITION_ALL"
        msg.motorID.append(armId)
        msg.angles = angles
        msg.speeds.append(speed)
        self.publisher.publish(msg)

    def moveBothArm(self, angles, speed):
        msg = Device_Arm_Msg()
        msg.command = "ARM_MOVE_TO_POSITION_ALL_BOTH"
        msg.angles = angles
        msg.speeds.append(speed)
        self.publisher.publish(msg)

    def moveArm(self):

        '''
        left arm movement
        '''
        speed = 30
        angles0 = [0, 0, 0]
        angles1 = [30, 20, -20]
        self.moveToPositionAll(0, angles1, speed)
        rospy.sleep(2)
        self.moveToPositionAll(0, angles0, speed)
        rospy.sleep(2)

        '''
        both arm moving
        '''
        speed = 60
        angles0 = [0, 0, 0, 0, 0, 0]
        angles1 = [120, 20, -20, 120, 20, -20]

        self.moveBothArm(angles1, speed)
        rospy.sleep(2)

        self.moveBothArm(angles0, speed)

if __name__ == "__main__" :
    rospy.init_node("move_arm_python", anonymous=False)
    arm = Arm()
    arm.moveArm()

#! /usr/bin/env python
'''
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
'''

import rospy
from silbot3_msgs.msg import Device_Wheel_Msg

def move_wheel() :
    publisher = rospy.Publisher('/DeviceNode/Wheel/commands', Device_Wheel_Msg, queue_size=10)
    wait_wheel_prepared(publisher)

    msg = Device_Wheel_Msg()
    msg.command = "WHEEL_MOVE_BY_VELOCITY_XYT"

    xvel = 200 # 100 mm / sec
    yvel = 200 # mm / sec
    theta = 30 # degree / sec
    msg.dParams = [xvel, yvel, theta]

    publisher.publish(msg)
    rospy.sleep(2)

    msg.dParams = [-xvel, -yvel, -theta]
    publisher.publish(msg)
    rospy.sleep(2)

    msg.dParams = [0, 0, 0]
    publisher.publish(msg)


def wait_wheel_prepared(publisher) :
    r = rospy.Rate(10)
    subscriber_count = publisher.get_num_connections()
    while subscriber_count < 1 :
        subscriber_count = publisher.get_num_connections()
        r.sleep()

if __name__ == "__main__" :
    rospy.init_node("move_wheel_python", anonymous=False)
    move_wheel()

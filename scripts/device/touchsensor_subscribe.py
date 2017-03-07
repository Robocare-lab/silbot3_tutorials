#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import Device_Touch_Msg

def callback(msg) :
    rospy.loginfo("touch button data " + str(msg))

def listen_touchsernser() :
    subscriber = rospy.Subscriber('/DeviceNode/TouchButton/data', Device_Touch_Msg, callback)

if __name__ == "__main__" :
    rospy.init_node("touch_listener_python", anonymous=True)
    listen_touchsernser()
    rospy.spin()

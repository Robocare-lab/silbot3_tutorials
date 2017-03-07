#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import Device_Ultra_Msg

def callback(msg) :
    rospy.loginfo("msg : " + str(msg))

def listen_sonarsensor() :
    subscriber = rospy.Subscriber('/DeviceNode/UltraSonic/data', Device_Ultra_Msg, callback)

if __name__ == "__main__" :
    rospy.init_node("touch_listener_python", anonymous=True)
    listen_sonarsensor()
    rospy.spin()

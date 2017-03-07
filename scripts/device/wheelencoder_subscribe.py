#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import Device_WheelEncoder_Msg

def callback(msg) :
    x = msg.x
    y = msg.y
    theta = msg.t
    rospy.loginfo("x : " + str(x) +", y : "+str(y) + " theta : " + str(theta))

def listen_touch() :
    subscriber = rospy.Subscriber('/DeviceNode/WheelEncoder/data', Device_WheelEncoder_Msg, callback)

if __name__ == "__main__" :
    rospy.init_node("wheelencoder_listener", anonymous=True)
    listen_touch()
    rospy.spin()

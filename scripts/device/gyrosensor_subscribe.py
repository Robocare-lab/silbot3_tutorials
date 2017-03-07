#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import Device_Gyro_Msg

def callback(msg) :
    rospy.loginfo("angle : " + str(msg.angle) +", rate : "+str(msg.rate))

def listen_sonarsensor() :
    subscriber = rospy.Subscriber('/DeviceNode/Gyro/data', Device_Gyro_Msg, callback)

if __name__ == "__main__" :
    rospy.init_node("gyro_listener_python", anonymous=True)
    listen_sonarsensor()
    rospy.spin()

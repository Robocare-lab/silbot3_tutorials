#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import Device_Wheel_Msg

def move_wheel():
    publisher = rospy.Publisher('/DeviceNode/Wheel/commands', Device_Wheel_Msg, queue_size=10)
    wait_wheel_prepared(publisher)
    msg = Device_Wheel_Msg()
    msg.command = "WHEEL_MOVE_TO_DELTA_X"

    deltaX = -1000
    velocity = 50

    msg.iParams.append(deltaX)
    msg.dParams.append(velocity)
    publisher.publish(msg)

def wait_wheel_prepared(publisher) :
    r = rospy.Rate(10)
    subscriber_count = publisher.get_num_connections()
    while subscriber_count < 1 :
        subscriber_count = publisher.get_num_connections()
        rospy.loginfo("wating for subscriber")
        r.sleep()

if __name__ == "__main__" :
    rospy.init_node("wheel_move_delta_python", anonymous=False)
    move_wheel()
    rospy.spin()

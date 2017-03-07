#!/usr/bin/env python
import rospy
import tf
from nav_msgs.msg import Odometry

def odom_callback(msg):
    rospy.loginfo(msg)

    x = msg.pose.pose.orientation.x
    y = msg.pose.pose.orientation.y
    z = msg.pose.pose.orientation.z
    w = msg.pose.pose.orientation.w

    '''
    quaternion to euler transformation
    '''
    euler = tf.transformations.euler_from_quaternion([x, y, z, w])
    roll = euler[0]
    pitch = euler[1]
    yaw = euler[2]

    rospy.loginfo("roll : %f, pitch : %f, yaw : %f " % (roll, pitch, yaw))

if __name__ == "__main__":
    rospy.init_node('oodometry', anonymous=True) #make node
    rospy.Subscriber('odom',Odometry, odom_callback)
    rospy.spin()
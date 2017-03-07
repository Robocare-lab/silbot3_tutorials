#! /usr/bin/env python
import rospy
from sensor_msgs.msg import LaserScan

def callback(msg) :
    logmsg = "\nheader : \n"
    logmsg += "\tseq : " + str(msg.header.seq) + "\n"
    logmsg += "\tstamp : \n"
    logmsg += "\t\t sec : " + str(msg.header.stamp.secs) +"\n"
    logmsg += "\t\t nsec : " + str(msg.header.stamp.nsecs) +"\n"
    logmsg += "\tframe_id : " + str(msg.header.frame_id)
    logmsg += "angle_min : " + str(msg.angle_min) +"\n"
    logmsg += "angle_max : " + str(msg.angle_min) +"\n"
    logmsg += "angle_increment : " + str(msg.angle_increment) +"\n"
    logmsg += "time_increment : " + str(msg.time_increment) +"\n"
    logmsg += "scan_time : " + str(msg.scan_time) +"\n"
    logmsg += "range_min : " + str(msg.range_min) +"\n"
    logmsg += "range_max : " + str(msg.range_max) +"\n"
    logmsg += "ranges : " + str(msg.ranges)
    rospy.loginfo(logmsg)

def listen_laserscanner() :
    subscriber = rospy.Subscriber('/scan', LaserScan, callback)

if __name__ == "__main__" :
    rospy.init_node("laserscaner_listener_python", anonymous=True)
    listen_laserscanner()
    rospy.spin()

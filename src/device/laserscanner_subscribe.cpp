#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <stdio.h>
#include <sstream>


using namespace std;

void callback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  stringstream ss;
  ss.clear();
  float size = (msg->angle_max - msg->angle_min)/msg->angle_increment;
  if(size < 0) {
    size = size*-1;
  }

  char* buffer = new char[10];
  for(int i=0; i<size ; i++) {
    if(i %10 ==0 ) {
      sprintf(buffer, "\n %3d] ", i);
      ss << buffer;
    }
    sprintf(buffer, "%.3f ", msg->ranges[i]);
    ss << buffer;
  }
  delete buffer;
  string rangeString = ss.str();

  ROS_INFO("\nheader : \n"
             "\tseq: %d\n"
             "\tstamp :\n"
               "\t\tsecs : %d\n"
               "\t\tnsecs: %d\n"
              "\tframe_id : %s\n"
          "angle_min : %f\n"
          "angle_max : %f\n"
          "angle_increment : %f\n"
          "time_increment : %f\n"
          "scan_time : %f\n"
          "range_min : %f\n"
          "range_max : %f\n"
          "range : %s",
    msg->header.seq,
      msg->header.stamp.sec,
      msg->header.stamp.nsec,
    msg->header.frame_id.c_str(),
  msg->angle_min,
  msg->angle_max,
  msg->angle_increment,
  msg->time_increment,
  msg->scan_time,
  msg->range_min,
  msg->range_max,
  rangeString.c_str()
  );


}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "laserscaner_listener_cpp");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/scan", 1000, callback);

  ros::spin();

  return 0;
}

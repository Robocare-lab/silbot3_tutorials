#include <ros/ros.h>
#include <silbot3_msgs/ExpressionStart.h>
#include <silbot3_msgs/ExpressionStatus.h>
#include <std_srvs/Empty.h>
#include <string>

using namespace std;

ros::ServiceClient startMotion;
ros::ServiceClient stopMotion;
ros::Subscriber subscriber;

int status;

void callback(const silbot3_msgs::ExpressionStatus::ConstPtr& msg)
{
  ROS_INFO("ExpressionStatus : %d", msg->expression_status);
  status = msg->expression_status;
}

void callMotion(string package, string category, string id, string sentence) {
  silbot3_msgs::ExpressionStart srv;
  srv.request.package = package;
  srv.request.category = category;
  srv.request.id = id;
  srv.request.content = sentence;

  if(startMotion.call(srv)) {
    ROS_INFO("callMotion %s , %s, %s, %s",package.c_str(), category.c_str(), id.c_str(), sentence.c_str());
  } else {
    ROS_ERROR("Failed to callMotion");
  }
  ROS_INFO("finish call");
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "motion_expression_cpp");
  ros::NodeHandle n;

  startMotion = n.serviceClient<silbot3_msgs::ExpressionStart>("/silbot3_expression/start");
  stopMotion = n.serviceClient<std_srvs::Empty>("/silbot3_expression/stop");

  subscriber = n.subscribe("/silbot3_expression/status", 1000, callback);
  status = -1;
  callMotion("office","guide","1","Hello World");

  while(status != 0) {
    ros::spinOnce();
  }
  ROS_INFO("finish motion expression");

  return 0;

}

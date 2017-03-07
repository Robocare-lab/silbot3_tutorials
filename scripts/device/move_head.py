#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import Device_ErobotPantilt_Msg
from silbot3_msgs.srv import Device_Data_Srv
from silbot3_msgs.srv import Device_Data_SrvRequest
from silbot3_msgs.srv import Device_Data_SrvResponse

'''
string command
int32[] motorID
float64[] angles
int32[] speeds
'''


'''
#define COMMAND_PANTILT_ON                              "PANTILT_ON"
#define COMMAND_PANTILT_OFF                             "PANTILT_OFF"
#define COMMAND_PANTILT_STOP                            "PANTILT_STOP"
#define COMMAND_PANTILT_MOVE_TO_HOME                    "PANTILT_MOVE_TO_HOME "
#define COMMAND_PANTILT_MOVE_TO_RELATIVE_POSITION       "PANTILT_MOVE_TO_RELATIVE_POSITION"
#define COMMAND_PANTILT_MOVE2MOTOR_SYNC                 "PANTILT_MOVE2MOTOR_SYNC"
#define COMMAND_PANTILT_MOVE_MOTOR                      "PANTILT_MOVE_MOTOR"
#define COMMAND_PANTILT_MOVE_ABSOLUTE_POSITION          "PANTILT_MOVE_ABSOLUTE_POSITION"
#define COMMAND_PANTILT_MOVE_ABSOLUTE_POSITION_WITH_SPEED           "PANTILT_MOVE_ABSOLUTE_POSITION_WITH_SPEED"
#define COMMAND_PANTILT_MOVE_ABSOLUTE_POSITION_ALL      "PANTILT_MOVE_ABSOLUTE_POSITION_ALL"
#define COMMAND_PANTILT_GETPOSITION                     "PANTILT_GETPOSITION"
#define COMMAND_PANTILT_SET_COMPLIANCE                  "PANTILT_SET_COMPLIANCE"
#define COMMAND_PANTILT_MOVE_XTION_TILT                 "PANTILT_MOVE_XTION_TILT"
#define COMMAND_PANTILT_GET_XTION_ANGLE                 "PANTILT_GET_XTION_ANGLE"
#define COMMAND_PANTILT_EMERGENCY_STOP                  "PANTILT_EMERGENCY_STOP"
#define COMMAND_PANTILT_EMERGENCY_RELEASE               "PANTILT_EMERGENCY_RELEASE"
#define COMMAND_PANTILT_DETECTING_ERROR                 "PANTILT_DETECTING_ERROR"
#define COMMAND_PANTILT_RELEASE_TORQUE                      "PANTILT_RELEASE_TORQUE"
#define COMMAND_PANTILT_START_TEACHING                      "PANTILT_START_TEACHING"
#define COMMAND_PANTILT_STOP_TEACHING                       "PANTILT_STOP_TEACHING"
'''

class Head :
    def __init__(self) :
        #self.service = rospy.ServiceProxy('/DeviceNode/PantiltDataService', Device_Data_Srv)
        self.publisher = rospy.Publisher('/DeviceNode/Pantilt/commands', Device_ErobotPantilt_Msg, queue_size=10)
        self.wait_head_prepared()
        #rospy.wait_for_service('/DeviceNode/PantiltDataService')

    def wait_head_prepared(self) :
        r = rospy.Rate(10)
        subscriber_count = self.publisher.get_num_connections()
        while subscriber_count < 1 :
            rospy.loginfo("wait for subsriber is valid...")
            subscriber_count = self.publisher.get_num_connections()
            r.sleep()

    def move_home(self, speed) :
        msg = Device_ErobotPantilt_Msg()
        msg.command = "PANTILT_MOVE_TO_HOME "
        msg.speeds.append(speed)
        self.publisher.publish(msg)
        rospy.loginfo("move_home published")

    def move_head(self, degLR, degUD, speed) :
        msg = Device_ErobotPantilt_Msg()
        msg.command = "PANTILT_MOVE_ABSOLUTE_POSITION"
        msg.angles.append(degLR)
        msg.angles.append(degUD)
        msg.speeds.append(speed)
        self.publisher.publish(msg)
        rospy.loginfo("move_head published")

    # def get_pantilt_position(self) :
    #     req = Device_Data_SrvRequest()
    #     req.command = "PANTILT_GETPOSITION"
    #     response = self.service(req)
    #     rospy.loginfo(response)

def head_moving() :
    head = Head()
    rospy.sleep(0.5)
    head.move_head(90, 0, 30)
    rospy.sleep(3)
    head.move_head(-90, 0, 30)
    rospy.sleep(6)
    head.move_head(0, 0, 30)
    rospy.sleep(3)
    head.move_head(20, 20, 20)
    rospy.sleep(1)
    head.move_head(0, 40, 40)
    rospy.sleep(1)
    head.move_head(0, 0, 40)
    rospy.sleep(1)
    head.move_head(20, 20, 20)
    rospy.sleep(1)
    head.move_head(0, 0, 20)
    rospy.sleep(1)

if __name__ == "__main__" :
    rospy.init_node("move_head_python", anonymous = True)
    head_moving()
    rospy.spin()

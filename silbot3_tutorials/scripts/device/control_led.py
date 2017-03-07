#! /usr/bin/env python
import rospy
from silbot3_msgs.msg import  Device_LED_Msg

class LED_Control :
    def __init__(self):
        self.publisher = rospy.Publisher("/DeviceNode/LED/commands", Device_LED_Msg, queue_size=10)

        while self.publisher.get_num_connections() < 1 :
            rospy.loginfo("Wait LED subscriber")
            rospy.sleep(0.1)

    def on(self, r, g, b):
        msg = Device_LED_Msg()
        msg.command = "on"
        msg.id = 0xF5
        msg.bright = 1
        msg.red = r
        msg.green = g
        msg.blue = b

        self.publisher.publish(msg)
        rospy.loginfo("published")


if __name__ == "__main__" :
    rospy.init_node("control_led_python", anonymous=False)
    led = LED_Control()
    led.on(1, 1, 1)
    rospy.sleep(1)
    led.on(1, 0, 0)
    rospy.sleep(1)
    led.on(0, 1, 0)
    rospy.sleep(1)
    led.on(0, 0, 1)
    rospy.sleep(1)
    led.on(0, 0, 0)

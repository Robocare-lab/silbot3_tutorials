#! /usr/bin/env python
import rospy
from std_msgs.msg import String

class PlaySound :
    def __init__(self):
        self.publisher = rospy.Publisher('/silbot3_sound/play', String, queue_size=10)
        self.wait_player_prepared()

    def play_sound(self, filepath):
        msg = String()
        msg.data = filepath
        self.publisher.publish(msg)

    def wait_player_prepared(self) :
        r = rospy.Rate(10)
        subscriber_count = self.publisher.get_num_connections()
        while subscriber_count < 1 :
            subscriber_count = self.publisher.get_num_connections()
            r.sleep()

if __name__ == "__main__" :
    rospy.init_node("play_sound_python", anonymous=False)
    player = PlaySound()
    player.play_sound("/opt/robocare/common/sound/effect/hi/hi.wav")

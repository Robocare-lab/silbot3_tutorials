#! /usr/bin/env python
'''
uint8 SPEAKER_ID_KOREAN_FEMALE=0
uint8 SPEAKER_ID_KOREAN_MALE=1
uint8 SPEAKER_ID_KOREAN_KID=2
uint8 SPEAKER_ID_ENGLISH_FEMALE=3
uint8 SPEAKER_ID_ENGLISH_MALE=4
uint8 SPEAKER_ID_DANISH_FEMALE=5
uint8 SPEAKER_ID_FINNISH_FEMALE=6
uint8 SPEAKER_ID_CHINESE_FEMALE=7
uint8 SPEAKER_ID_CHINESE_MALE=8
uint8 speaker_id
uint8 speed
uint8 volume
uint8 pitch
'''

'''
string text
string filepath
---
uint8 TTS_RESULT_SUCCESS=0
uint8 TTS_RESULT_FAILED=1
uint8 tts_result
silbot3_msgs/TTSViseme[] tts_viseme_array
  uint8 id
  uint16 duration
'''
import rospy
from silbot3_msgs.msg import TTSSetProperties
from silbot3_msgs.srv import TTSMake
from silbot3_msgs.srv import TTSMakeRequest

class MakeTTS :
    def __init__(self):
        self.make_service_client = rospy.ServiceProxy('/silbot3_tts/make', TTSMake)
        self.set_publisher = rospy.Publisher('/silbot3_tts/set_properties', TTSSetProperties, queue_size=10)
        self.wait_prepared()

    def setProperty(self, lang, speed, volume, pitch):
        msg = TTSSetProperties()
        msg.speaker_id = lang
        msg.speed = speed
        msg.volume = volume
        msg.pitch = pitch
        self.set_publisher.publish(msg)

    def make(self, text, filepath):
        req = TTSMakeRequest()
        req.text = text
        req.filepath = filepath
        res = self.make_service_client(req)
        rospy.loginfo("make_tts : " + str(res))

    def wait_prepared(self) :
        r = rospy.Rate(10)
        subscriber_count = self.set_publisher.get_num_connections()
        while subscriber_count < 1 :
            subscriber_count = self.set_publisher.get_num_connections()
            r.sleep()

if __name__ == "__main__" :
    rospy.init_node("make_tts_python", anonymous=False)
    make = MakeTTS()
    make.setProperty(3,100,100,100)
    rospy.sleep(1)
    make.make("hello","/tmp/hello.wav")

#! /usr/bin/env python
# -*- coding: utf-8 -*-
#
import sys
import rospy
import cv2
import numpy as np
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError



class image_converter :
    def __init__(self):
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/camera/depth/image_raw", Image, self.callback)

    def callback(self, data):
        cv_image = None
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "passthrough")
            cv_image = np.array(cv_image, dtype=np.float32)
            cv2.normalize(cv_image, cv_image, 0, 1, cv2.NORM_MINMAX)
        except CvBridgeError as e:
            print(e)

        if cv_image is not None :
            cv2.imshow("Image window", cv_image)
            cv2.waitKey(3)

if __name__ == "__main__" :
    rospy.init_node('camera_rgb_viewer', anonymous=True)
    image_proc = image_converter()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    cv2.destroyAllWindows()

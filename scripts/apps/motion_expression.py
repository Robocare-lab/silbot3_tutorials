#! /usr/bin/env python
import rospy
import threading
from concurrent.futures import ThreadPoolExecutor
import time
from silbot3_msgs.srv import ExpressionStart
from silbot3_msgs.srv import ExpressionStartRequest
from silbot3_msgs.msg import ExpressionStatus

class MotionExpression :
    def __init__(self):
        self.startMotion = rospy.ServiceProxy('/silbot3_expression/start', ExpressionStart)
        self.stopMotion = rospy.ServiceProxy('/silbot3_expression/stop', ExpressionStart)
        self.subscriber = rospy.Subscriber('/silbot3_expression/status', ExpressionStatus, self.expresionCallback)
        self.expressionCondition = threading.Condition()
        self.motionFinished = True

        rospy.loginfo("wait for motion service")
        self.startMotion.wait_for_service()
        self.stopMotion.wait_for_service()
        rospy.loginfo("Found motion service")

    def callMotion(self, package, category, id, sentence):
        req = ExpressionStartRequest()
        req.expression_type = 0
        req.package = package
        req.category = category
        req.id = id
        req.content = sentence
        res = self.startMotion(req)
        rospy.loginfo("callMotion : " + str(res))

    def waitExpressionFinish(self):
        if self.motionFinished is not True :
            self.expressionCondition.wait()

    def expresionCallback(self, msg):
        rospy.loginfo(msg)

if __name__ == "__main__" :
    rospy.init_node("motion_expression_python", anonymous=False)
    expression = MotionExpression()
    expression.callMotion("office","guide","1","Hello World")
    expression.waitExpressionFinish()

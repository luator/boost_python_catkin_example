#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy

import sys
# TODO: this is ugly... can this be set using cmake?
sys.path.append("/home/felix/ws/ros/devel/lib")

import libmycpplib as cpp

# this is the equivalent to `main()` in c++
if __name__ == '__main__':
    rospy.init_node('use_cpplib')

    cpp.hello()

    #rospy.spin()

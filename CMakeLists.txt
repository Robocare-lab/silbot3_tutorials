cmake_minimum_required(VERSION 2.8.3)
project(silbot3_tutorials)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  silbot3_msgs
  std_msgs
  sensor_msgs
  cv_bridge
  image_transport
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

# Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   sensor_msgs#   silbot3_msgs#   std_msgs
)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES silbot3_tutorials
#  CATKIN_DEPENDS roscpp rospy sensor_msgs silbot3_msgs std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(touchsensor_subscribe src/device/touchsensor_subscribe.cpp)
target_link_libraries(touchsensor_subscribe
   ${catkin_LIBRARIES}
)

add_executable(sonarsensor_subscribe src/device/sonarsensor_subscribe.cpp)
target_link_libraries(sonarsensor_subscribe
   ${catkin_LIBRARIES}
)

add_executable(wheelencoder_subscribe src/device/wheelencoder_subscribe.cpp)
target_link_libraries(wheelencoder_subscribe
   ${catkin_LIBRARIES}
)

add_executable(gyrosensor_subscribe src/device/gyrosensor_subscribe.cpp)
target_link_libraries(gyrosensor_subscribe
   ${catkin_LIBRARIES}
)

add_executable(laserscanner_subscribe src/device/laserscanner_subscribe.cpp)
target_link_libraries(laserscanner_subscribe
   ${catkin_LIBRARIES}
)

add_executable(move_arm src/device/move_arm.cpp)
target_link_libraries(move_arm
   ${catkin_LIBRARIES}
)

add_executable(move_head src/device/move_head.cpp)
target_link_libraries(move_head
   ${catkin_LIBRARIES}
)

add_executable(move_wheel src/device/move_wheel.cpp)
target_link_libraries(move_wheel
   ${catkin_LIBRARIES}
)

add_executable(control_led src/device/control_led.cpp)
target_link_libraries(control_led
   ${catkin_LIBRARIES}
)


add_executable(rgb_image_subscribe src/device/rgb_image_subscribe.cpp)
target_link_libraries(rgb_image_subscribe
   ${catkin_LIBRARIES}
)

add_executable(depth_image_subscribe src/device/depth_image_subscribe.cpp)
target_link_libraries(depth_image_subscribe
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
)



add_executable(motion_expression src/apps/motion_expression.cpp)
target_link_libraries(motion_expression
   ${catkin_LIBRARIES}
)
#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS silbot3_tutorials silbot3_tutorials_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

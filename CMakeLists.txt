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
add_dependencies(touchsensor_subscribe silbot3_msgs_generate_messages_cpp)
target_link_libraries(touchsensor_subscribe
   ${catkin_LIBRARIES}
)

add_executable(sonarsensor_subscribe src/device/sonarsensor_subscribe.cpp)
add_dependencies(sonarsensor_subscribe silbot3_msgs_generate_messages_cpp)
target_link_libraries(sonarsensor_subscribe
   ${catkin_LIBRARIES}
)

add_executable(wheelencoder_subscribe src/device/wheelencoder_subscribe.cpp)
add_dependencies(wheelencoder_subscribe silbot3_msgs_generate_messages_cpp)
target_link_libraries(wheelencoder_subscribe
   ${catkin_LIBRARIES}
)

add_executable(gyrosensor_subscribe src/device/gyrosensor_subscribe.cpp)
add_dependencies(gyrosensor_subscribe silbot3_msgs_generate_messages_cpp)
target_link_libraries(gyrosensor_subscribe
   ${catkin_LIBRARIES}
)

add_executable(laserscanner_subscribe src/device/laserscanner_subscribe.cpp)
target_link_libraries(laserscanner_subscribe
   ${catkin_LIBRARIES}
)

add_executable(move_arm src/device/move_arm.cpp)
add_dependencies(move_arm silbot3_msgs_generate_messages_cpp)
target_link_libraries(move_arm
   ${catkin_LIBRARIES}
)

add_executable(move_head src/device/move_head.cpp)
add_dependencies(move_head silbot3_msgs_generate_messages_cpp)
target_link_libraries(move_head
   ${catkin_LIBRARIES}
)

add_executable(move_wheel src/device/move_wheel.cpp)
add_dependencies(move_wheel silbot3_msgs_generate_messages_cpp)
target_link_libraries(move_wheel
   ${catkin_LIBRARIES}
)

add_executable(control_led src/device/control_led.cpp)
add_dependencies(control_led silbot3_msgs_generate_messages_cpp)
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
add_dependencies(motion_expression silbot3_msgs_generate_messages_cpp)
target_link_libraries(motion_expression
   ${catkin_LIBRARIES}
)

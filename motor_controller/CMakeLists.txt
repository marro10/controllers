cmake_minimum_required(VERSION 2.8.3)
project(motor_controller)

find_package(catkin REQUIRED COMPONENTS roscpp ras_arduino_msgs)
# std_msgs)
find_package(common REQUIRED)
find_package(ras_arduino_msgs REQUIRED)

################################################
## Declare ROS messages, services and actions ##
################################################

catkin_package()

###########
## Build ##
###########

include_directories(${common_INCLUDE_DIRS})

include_directories(include ${catkin_INCLUDE_DIRS}
					"../etc")

add_executable(motor_controller motor_controller.cpp)
add_executable(constant_calibrator constant_calibrator.cpp)
target_link_libraries(motor_controller ${catkin_LIBRARIES} ${common_LIBRARIES})
target_link_libraries(constant_calibrator ${catkin_LIBRARIES} ${common_LIBRARIES})

#############
## Install ##
#############


#############
## Testing ##
#############


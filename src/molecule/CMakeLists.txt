cmake_minimum_required(VERSION 2.8.3)
project(molecule)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED

	roscpp
	visualization_msgs
	message_generation

)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )


## Generate added messages and services with any dependencies listed here
#generate_messages(
#   DEPENDENCIES
#   visualization_msgs  # Or other packages containing msgs
#)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES molecule
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories( include ${catkin_INCLUDE_DIRS} )


#add_executable(h20 src/molecule.cpp)
#target_link_libraries(molecule ${catkin_LIBRARIES})
#add_dependencies(h20 molecule_generate_messages_cpp)


add_executable(molecule src/molecule.cpp)
target_link_libraries(molecule ${catkin_LIBRARIES})
add_dependencies(molecule molecule_generate_messages_cpp)


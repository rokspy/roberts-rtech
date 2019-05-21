cmake_minimum_required(VERSION 2.8.3)
project(deneb)


find_package(catkin REQUIRED
	roscpp
	std_msgs
	message_generation
)

add_message_files(
	FILES
	angles.msg
)


generate_messages(
	DEPENDENCIES
	std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES deneb
  CATKIN_DEPENDS message_runtime
#  DEPENDS eigen3
)



###########
## Build ##
###########


include_directories(include ${catkin_INCLUDE_DIRS})

link_directories(/usr/local/include)

add_executable(counter src/counter.cpp)
target_link_libraries(counter ${catkin_LIBRARIES})
add_dependencies(counter messaging_generate_messages_cpp)




cmake_minimum_required(VERSION 2.8.3)
project(trytry)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
	roscpp
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(example src/trym.cpp)
target_link_libraries(example ${catkin_LIBRARIES})

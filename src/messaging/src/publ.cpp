#include "ros/ros.h"
#include "sensor_msgs/Range.h"
#include "std_msgs/Float32.h"
#include <sstream>

int main (int argc, char **argv){


	ros::init(argc, argv, "publ");

	ros::NodeHandle n;

	ros::Publisher publii_pub = n.advertise<sensor_msgs::Range>("publii", 1000);

	ros::Rate loop_rate(1);

	sensor_msgs::Range msg;

	msg.field_of_view = 0.7855;
	msg.min_range = 0.02;
	msg.max_range = 4.00;
	msg.range = 1.0'
	
	while (ros::ok()){

		//ROS_INFO("%.2f", msg.range);

		publii_pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();
		msg.range ++;
	}
	return 0;
}

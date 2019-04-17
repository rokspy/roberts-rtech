#include "ros/ros.h"
#include "sensor_msgs/Range.h"
#include "std_msgs/Float32.h"
#include <sstream>
#include <cstdlib>


#define PI 3.14159

float RandomFloat(float a, float b){
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
 
}


int main (int argc, char **argv){
	
	ros::init(argc, argv, "publ");
		
	ros::NodeHandle n;

	ros::Publisher publii_pub = n.advertise<sensor_msgs::Range>("publii", 1000);

	ros::Rate loop_rate(1);

	sensor_msgs::Range msg;

	msg.field_of_view = 0.7855;
	msg.min_range = 0.02;
	msg.max_range = 4.00;
	msg.header.frame_id = "base_link";
	msg.field_of_view = PI/3;
	msg.radiation_type = 0;

	while (ros::ok()){

		//ROS_INFO("%.2f", msg.range);
		msg.range = RandomFloat(msg.min_range, msg.max_range);		

		publii_pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();
		msg.range ++;
	}
	return 0;
}

#include "ros/ros.h"
#include "sensor_msgs/Range.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"
#include <sstream>
#include <cstdlib>


#define PI 3.14159


sensor_msgs::Range glob_data;

float filter(float data){
	
	return data = floor(data*100)/100;
	
}

void chatterCallback(const sensor_msgs::Range message){
	glob_data = message;

}

int main (int argc, char **argv){


	ros::init(argc, argv, "publ");
		
	ros::NodeHandle n, m;
	
	ros::Subscriber data = m.subscribe<sensor_msgs::Range>("chatter",1000,chatterCallback);
	ros::Publisher publii_pub = n.advertise<sensor_msgs::Range>("publii", 1000);

	ros::Rate loop_rate(5);

	sensor_msgs::Range msg;

	 
	while (ros::ok()){
		

					
		msg = glob_data;
		msg.range = filter(msg.range);
		
		//ROS_INFO("%f", glob_data.range);
		//msg.range = glob_data.range;
		publii_pub.publish(msg);


		ros::spinOnce();

		loop_rate.sleep();
		msg.range ++;

	}
	return 0;
}

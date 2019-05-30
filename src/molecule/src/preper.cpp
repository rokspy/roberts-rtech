#include "ros/ros.h"
#include "visualization_msgs/Marker.h"




int main(int argc, char **argv){

	ros::init(argc,argv,"molecule");

	ros::NodeHandle n;
	


	ros::Publisher h20 = n.advertise<visualization_msgs::Marker>("molec_info", 0);


return 0;

}




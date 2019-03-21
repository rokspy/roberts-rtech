#include "ros/ros.h"
#include "std_msgs/Float32.h"


void dividerCallback(std_msgs::Float32 msg){

//	msg.data = msg.data / 2;
//	ros::Rate loop_rate(1);
//	divider_pub.publish(msg);
//	ROS_INFO("I heard: [%.2f]", msg.data);
//	while(ros::ok()){
//		ROS_INFO("I heard: [%.2f]", msg.data);
//		ros::Duration(1).sleep();
//		divider_pub.publish(msg);
//		ros::spinOnce();
//		loop_rate.sleep();
//	}

}

int main(int argc, char **argv){

	ros::init(argc, argv, "divider");
	ros::NodeHandle n;
	ros::NodeHandle m;

	ros::Publisher divider_pub = m.advertise<std_msgs::Float32>("TV",1000);
	ros::Subscriber sub = n.subscribe("chatter",1000, dividerCallback);

	ros::spin();
	return 0;
}

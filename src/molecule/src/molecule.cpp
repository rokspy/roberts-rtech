#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Twist.h"


geometry_msgs::Twist recieved;


void somCallback(const geometry_msgs::Twist message){
	recieved = message;
}



int main(int argc, char **argv){

	ros::init(argc,argv,"molecule");

	ros::NodeHandle n;
	ros::NodeHandle m;

	ros::Subscriber movement = m.subscribe<geometry_msgs::Twist>("cmd_vel",1000,somCallback);
	ros::Publisher h20 = n.advertise<visualization_msgs::Marker>("molec_info", 0);


	visualization_msgs::Marker oxygen;
	oxygen.header.frame_id = "map";
	oxygen.header.stamp = ros::Time();
	oxygen.ns = "my_namespace";
	oxygen.id = 0;

	visualization_msgs::Marker bond_1;
	bond_1.header.frame_id = "map";
	bond_1.header.stamp = ros::Time();
	bond_1.ns = "my_namespace";
	bond_1.id = 1;

	visualization_msgs::Marker bond_2;
	bond_2.header.frame_id = "map";
	bond_2.header.stamp = ros::Time();
	bond_2.ns = "my_namespace";
	bond_2.id = 2;

	visualization_msgs::Marker hydrogen_1;
	hydrogen_1.header.frame_id = "map";
	hydrogen_1.header.stamp = ros::Time();
	hydrogen_1.ns = "my_namespace";
	hydrogen_1.id = 3;

	visualization_msgs::Marker hydrogen_2;
	hydrogen_2.header.frame_id = "map";
	hydrogen_2.header.stamp = ros::Time();
	hydrogen_2.ns = "my_namespace";
	hydrogen_2.id = 4;
	
	oxygen.type = visualization_msgs::Marker::SPHERE;
	bond_1.type = visualization_msgs::Marker::CYLINDER;
	bond_2.type = visualization_msgs::Marker::CYLINDER;
	hydrogen_1.type = visualization_msgs::Marker::SPHERE;
	hydrogen_2.type = visualization_msgs::Marker::SPHERE;


	ros::Rate loop_rate(5);


oxygen.pose.position.x = 0;
oxygen.pose.position.y = 0;
oxygen.pose.position.z = 0;
oxygen.pose.orientation.x = 0.0;
oxygen.pose.orientation.y = 0.0;
oxygen.pose.orientation.z = 0.0;
oxygen.pose.orientation.w = 1.0;
oxygen.scale.x = 1;
oxygen.scale.y = 1;
oxygen.scale.z = 1;
oxygen.color.a = 1.0;
oxygen.color.r = 1.0;
oxygen.color.g = 0.0;
oxygen.color.b = 0.0;


bond_1.pose.position.x = 0;
bond_1.pose.position.y = 0.6;
bond_1.pose.position.z = -0.35;
bond_1.pose.orientation.x = 0.5;
bond_1.pose.orientation.y = 0.0;
bond_1.pose.orientation.z = 0.0;
bond_1.pose.orientation.w = 1.0;
bond_1.scale.x = 0.2;
bond_1.scale.y = 0.2;
bond_1.scale.z = 1.5;
bond_1.color.a = 1.0;
bond_1.color.r = 0.7;
bond_1.color.g = 0.7;
bond_1.color.b = 0.7;


bond_2.pose.position.x = 0;
bond_2.pose.position.y = -0.6;
bond_2.pose.position.z = -0.35;
bond_2.pose.orientation.x = -0.5;
bond_2.pose.orientation.y = 0.0;
bond_2.pose.orientation.z = 0.0;
bond_2.pose.orientation.w = 1.0;
bond_2.scale.x = 0.2;
bond_2.scale.y = 0.2;
bond_2.scale.z = 1.5;
bond_2.color.a = 1.0;
bond_2.color.r = 0.7;
bond_2.color.g = 0.7;
bond_2.color.b = 0.7;


hydrogen_1.pose.position.x = 0;
hydrogen_1.pose.position.y = 1.2;
hydrogen_1.pose.position.z = -0.8;
hydrogen_1.pose.orientation.x = 0.5;
hydrogen_1.pose.orientation.y = 0.0;
hydrogen_1.pose.orientation.z = 0.0;
hydrogen_1.pose.orientation.w = 1.0;
hydrogen_1.scale.x = 0.7;
hydrogen_1.scale.y = 0.7;
hydrogen_1.scale.z = 0.7;
hydrogen_1.color.a = 1.0;
hydrogen_1.color.r = 1;
hydrogen_1.color.g = 1;
hydrogen_1.color.b = 1;


hydrogen_2.pose.position.x = 0;
hydrogen_2.pose.position.y = -1.2;
hydrogen_2.pose.position.z = -0.8;
hydrogen_2.pose.orientation.x = -0.5;
hydrogen_2.pose.orientation.y = 0.0;
hydrogen_2.pose.orientation.z = 0.0;
hydrogen_2.pose.orientation.w = 1.0;
hydrogen_2.scale.x = 0.7;
hydrogen_2.scale.y = 0.7;
hydrogen_2.scale.z = 0.7;
hydrogen_2.color.a = 1.0;
hydrogen_2.color.r = 1;
hydrogen_2.color.g = 1;
hydrogen_2.color.b = 1;




while(ros::ok()){


oxygen.pose.position.x = oxygen.pose.position.x + recieved.linear.x/10;
oxygen.pose.position.y = oxygen.pose.position.y + recieved.angular.z/10;

hydrogen_1.pose.position.x = hydrogen_1.pose.position.x + recieved.linear.x/10;
hydrogen_1.pose.position.y = hydrogen_1.pose.position.y + recieved.angular.z/10;

hydrogen_2.pose.position.x = hydrogen_2.pose.position.x + recieved.linear.x/10;
hydrogen_2.pose.position.y = hydrogen_2.pose.position.y + recieved.angular.z/10;

bond_1.pose.position.x = bond_1.pose.position.x + recieved.linear.x/10;
bond_1.pose.position.y = bond_1.pose.position.y + recieved.angular.z/10;

bond_2.pose.position.x = bond_2.pose.position.x + recieved.linear.x/10;
bond_2.pose.position.y = bond_2.pose.position.y + recieved.angular.z/10;



h20.publish( oxygen );
h20.publish( bond_1 );
h20.publish( bond_2 );
h20.publish( hydrogen_1 );
h20.publish( hydrogen_2 );

recieved.linear.x = 0;
recieved.angular.z = 0;


ros::spinOnce();
loop_rate.sleep();

}
return 0;

}





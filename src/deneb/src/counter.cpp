#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "deneb/angles.h"
#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Dense>
#include <time.h>
#include <fstream>

#define DegRad 57.2957795


char currentDateTime(int k){
	time_t 		now = time(0);
	struct tm 	tsruct;
	char   		buf[80];
	tsruct = *localtime(&now);
	
	strftime(buf, sizeof(buf), "%X", &tsruct);
	
	return buf[k];
}


int main(int argc, char **argv){
	
	ros::init(argc, argv, "publ");
		
	ros::NodeHandle m;
	ros::Publisher angles = m.advertise<deneb::angles>("new_angles",1000);

	std::ofstream isfile;
	std::ofstream isfile_2;
	isfile.open("stardata.txt");
	isfile_2.open("stardata_2.txt");


	char timeis[8];
	int count = 0;

	long double n, dot_prod, magn, cosalpha_1, cosalpha_2, new_alt, new_az;
	Eigen::Matrix<long double, 1,3> da, axis, vector_rot, cross_prod, vector_rot_proj, north;
	
	north << 0,1,0;
	axis << 0,0.5299, 0.8480;

	double altitude = 51.11;
	double azimuth = 96.36;
	long double rotation = 0;
	long double earth_rot = 0.000072921159;
	
	std::cout << "Input Altitude: ";
	std::cin >> altitude;
	std::cout << "\nInput Azimuth: ";
	std:: cin >> azimuth;
	std::cout << std::endl;
	

	da(0) = north(0)*cos(azimuth/DegRad) + north(1)*sin(azimuth/DegRad);
	da(1) = -1 * north(0)*sin(azimuth/DegRad) + north(1)*cos(azimuth/DegRad);
	
	n = cos(altitude/DegRad);

	da(0) = da(0) * n;
	da(1) = da(1) * n;

	da(2) = sqrtf(pow(da(0),2) + pow(da(1),2));
	da(2) = sqrtf(1 - pow(da(2),2));

	dot_prod = da.dot(axis);
	cross_prod = axis.cross(da);

	deneb::angles new_angles;

	//for(int k=0; k<8; k++){
	//	timeis[k] = currentDateTime(k);
	//}

	rotation = 0;
	ros::Rate loop_rate(1);
	while(ros::ok()){
		
		if(count == 3600){
			count = 0;
		}
		


		rotation = rotation - earth_rot; // Maybe should be removed in first loop for precision

		vector_rot = da*cos(rotation) + cross_prod*sin(rotation) + axis*dot_prod*(1-cos(rotation));

		vector_rot_proj = vector_rot;
		vector_rot_proj(2) = 0;


		magn = sqrtf(pow(vector_rot_proj(0),2) + pow(vector_rot_proj(1),2) + pow(vector_rot_proj(2),2));

		cosalpha_1 = vector_rot.dot(vector_rot_proj)/magn;
		new_angles.altitude = acos(cosalpha_1) * DegRad;

		cosalpha_2 = north.dot(vector_rot_proj)/magn;
		new_angles.azimuth = acos(cosalpha_2) * DegRad;

		if(vector_rot_proj(0)<0){
			new_angles.azimuth = 360-new_angles.azimuth;
		}
		if(vector_rot_proj(2)<0){
			new_angles.altitude = new_angles.altitude * (-1);
		}


		for(int k=0; k<8; k++){
			timeis[k] = currentDateTime(k);
		}

		if(count == 0){
			for(int k=0; k<8; k++){
				isfile << timeis[k];
			}
			isfile << "  |  Altitude = " << new_angles.altitude << "  |  Azimuth = " << new_angles.azimuth << "\n";
		}

		

		// Writting angle values when azimuth reaches N,E,S,W

		if(new_angles.azimuth > 359.990 || new_angles.azimuth < 0.015){
			for(int k=0; k<8; k++){
				isfile_2 << timeis[k];
			}
			isfile_2 << "  |  Altitude = " << new_angles.altitude << "  |  Azimuth = " << new_angles.azimuth << "\n";
		}
		if(new_angles.azimuth > 89.99 && new_angles.azimuth < 90.01){
			for(int k=0; k<8; k++){
				isfile_2 << timeis[k];
			}
			isfile_2 << "  |  Altitude = " << new_angles.altitude << "  |  Azimuth = " << new_angles.azimuth << "\n";
		}
		if(new_angles.azimuth > 179.99 && new_angles.azimuth < 180.01){
			for(int k=0; k<8; k++){
				isfile_2 << timeis[k];
			}
			isfile_2 << "  |  Altitude = " << new_angles.altitude << "  |  Azimuth = " << new_angles.azimuth << "\n";
		}
		if(new_angles.azimuth > 269.99 && new_angles.azimuth < 270.01){
			for(int k=0; k<8; k++){
				isfile_2 << timeis[k];
			}
			isfile_2 << "  |  Altitude = " << new_angles.altitude << "  |  Azimuth = " << new_angles.azimuth << "\n";
		}
		

		angles.publish(new_angles);

		count++;
		ros::spinOnce();
		loop_rate.sleep();
	}



isfile.close();
return 0;
}

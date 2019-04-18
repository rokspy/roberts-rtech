
#include <ros.h>
#include <sensor_msgs/Range.h>


// Ultrasonic sensor pins
int echoPin = A3;
int trigPin = A2;

ros::NodeHandle  n;



sensor_msgs::Range sensor;
ros::Publisher chatter("chatter", &sensor);


void setup()
{
  sensor.header.frame_id = "base_link";
  sensor.radiation_type = 0;
  sensor.field_of_view = 3.1459/12; 
  sensor.min_range = 0.02;
  sensor.max_range = 4;
  n.initNode();
  n.advertise(chatter);
  Serial.begin(57600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);

}

double getSonarReadingMeters()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  double duration_us = pulseIn(echoPin, HIGH);
  double distance_m = (duration_us / 58.0)*0.01;
  return distance_m;
}

void loop()
{
  double us = getSonarReadingMeters(); //Get distance from wall with ultrasonic sensor
  Serial.println(us);
  sensor.range = us;
  chatter.publish( &sensor);
  n.spinOnce();
  delay(200);
}

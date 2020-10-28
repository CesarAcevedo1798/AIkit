#include <ros/ros.h>
#include <tf/tf.h>
#include <sensor_msgs/Imu.h>

double imuValues1[4] = {0,0,0,1};
double imuValues2[4] = {0,0,0,1};
double imuValues3[4] = {0,0,0,1};
double imuValues4[4] = {0,0,0,1};
tf::Quaternion q1(1,0,0,0);
tf::Matrix3x3 m1(q1);
geometry_msgs::Vector3 a1;
geometry_msgs::Vector3 w1;

void AIkit1Callback(const sensor_msgs::Imu::ConstPtr &values)
{
  imuValues1[0] = values->orientation.x;
  imuValues1[1] = values->orientation.y;
  imuValues1[2] = values->orientation.z;
  imuValues1[3] = values->orientation.w;
  /*q1.x =imuValues1[0];
  q1.y =imuValues1[1];
  q1.z =imuValues1[2];
  q1.w =imuValues1[3];*/
  tf::Quaternion q(imuValues1[0],imuValues1[1],imuValues1[2],imuValues1[3]);
  a1.x = values->linear_acceleration.z;
  a1.y = values->linear_acceleration.x;
  a1.z = values->linear_acceleration.y;
  w1.x = values->angular_velocity.z;
  w1.y = values->angular_velocity.x;
  w1.z = values->angular_velocity.y;
  tf::Matrix3x3 m(q);
  m1.setValue(m[0][2],m[0][0],m[0][1],m[1][2],m[1][0],m[1][1],m[2][2],m[2][0],m[2][1]);
  m1.getRotation(q1);

}

int main(int argc, char** argv){
  ros::init(argc, argv, "AIkit_republisher");
  ros::NodeHandle n;

  ros::Rate r(10);
  ros::Subscriber AIkit1_sub = n.subscribe("aikit1/imu",10,AIkit1Callback);
  ros::Publisher AIkit1_pub = n.advertise<sensor_msgs::Imu>("AIkit1r/imu", 10);

  geometry_msgs::Quaternion q1msg;

  while(n.ok()){
    sensor_msgs::Imu imu1;
    tf::quaternionTFToMsg(q1,q1msg);
    imu1.orientation = q1msg;
    imu1.orientation_covariance = {0,0,0,0,0,0,0,0,0};
    imu1.linear_acceleration = a1;
    imu1.linear_acceleration_covariance = {0,0,0,0,0,0,0,0,0};
    imu1.angular_velocity = w1;
    imu1.angular_velocity_covariance = {0,0,0,0,0,0,0,0,0};
    AIkit1_pub.publish(imu1);
    ros::spinOnce();
    r.sleep();
  }
}
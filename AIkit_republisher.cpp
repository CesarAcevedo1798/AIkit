#include <ros/ros.h>
#include <tf/tf.h>
#include <sensor_msgs/Imu.h>

#define NODERATE 50

double imuValues1[4] = {0,0,0,1};
double imuValues2[4] = {0,0,0,1};
double imuValues3[4] = {0,0,0,1};
double imuValues4[4] = {0,0,0,1};

tf::Quaternion q1(0,0,0,1);
tf::Quaternion q2(0,0,0,1);
tf::Quaternion q3(0,0,0,1);
tf::Quaternion q4(0,0,0,1);

tf::Matrix3x3 m1(q1);
tf::Matrix3x3 m2(q2);
tf::Matrix3x3 m3(q3);
tf::Matrix3x3 m4(q4);

geometry_msgs::Vector3 a1;
geometry_msgs::Vector3 a2;
geometry_msgs::Vector3 a3;
geometry_msgs::Vector3 a4;
geometry_msgs::Vector3 w1;
geometry_msgs::Vector3 w2;
geometry_msgs::Vector3 w3;
geometry_msgs::Vector3 w4;

void AIkit1Callback(const sensor_msgs::Imu::ConstPtr &values)
{
  imuValues1[0] = values->orientation.x;
  imuValues1[1] = values->orientation.y;
  imuValues1[2] = values->orientation.z;
  imuValues1[3] = values->orientation.w;
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

void AIkit2Callback(const sensor_msgs::Imu::ConstPtr &values)
{
  imuValues2[0] = values->orientation.x;
  imuValues2[1] = values->orientation.y;
  imuValues2[2] = values->orientation.z;
  imuValues2[3] = values->orientation.w;
  tf::Quaternion q(imuValues2[0],imuValues2[1],imuValues2[2],imuValues2[3]);
  a2.x = values->linear_acceleration.z;
  a2.y = values->linear_acceleration.x;
  a2.z = values->linear_acceleration.y;
  w2.x = values->angular_velocity.z;
  w2.y = values->angular_velocity.x;
  w2.z = values->angular_velocity.y;
  tf::Matrix3x3 m(q);
  m2.setValue(m[0][2],m[0][0],m[0][1],m[1][2],m[1][0],m[1][1],m[2][2],m[2][0],m[2][1]);
  m2.getRotation(q2);
}

void AIkit3Callback(const sensor_msgs::Imu::ConstPtr &values)
{
  imuValues3[0] = values->orientation.x;
  imuValues3[1] = values->orientation.y;
  imuValues3[2] = values->orientation.z;
  imuValues3[3] = values->orientation.w;
  tf::Quaternion q(imuValues3[0],imuValues3[1],imuValues3[2],imuValues3[3]);
  a1.x = values->linear_acceleration.z;
  a1.y = values->linear_acceleration.x;
  a1.z = values->linear_acceleration.y;
  w1.x = values->angular_velocity.z;
  w1.y = values->angular_velocity.x;
  w1.z = values->angular_velocity.y;
  tf::Matrix3x3 m(q);
  m3.setValue(m[0][2],m[0][0],m[0][1],m[1][2],m[1][0],m[1][1],m[2][2],m[2][0],m[2][1]);
  m3.getRotation(q3);
}

void AIkit4Callback(const sensor_msgs::Imu::ConstPtr &values)
{
  imuValues4[0] = values->orientation.x;
  imuValues4[1] = values->orientation.y;
  imuValues4[2] = values->orientation.z;
  imuValues4[3] = values->orientation.w;
  tf::Quaternion q(imuValues1[0],imuValues1[1],imuValues1[2],imuValues1[3]);
  a4.x = values->linear_acceleration.z;
  a4.y = values->linear_acceleration.x;
  a4.z = values->linear_acceleration.y;
  w4.x = values->angular_velocity.z;
  w4.y = values->angular_velocity.x;
  w4.z = values->angular_velocity.y;
  tf::Matrix3x3 m(q);
  m4.setValue(m[0][2],m[0][0],m[0][1],m[1][2],m[1][0],m[1][1],m[2][2],m[2][0],m[2][1]);
  m4.getRotation(q4);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "AIkit_republisher");
  ros::NodeHandle n;

  ros::Rate r(NODERATE);

  //republish AIkit1 data
  ros::Subscriber AIkit1_sub = n.subscribe("aikit1/imu",10,AIkit1Callback);
  ros::Publisher AIkit1_pub = n.advertise<sensor_msgs::Imu>("AIkit1r/imu", 10);

  //republish AIkit2 data
  ros::Subscriber AIkit2_sub = n.subscribe("aikit2/imu",10,AIkit2Callback);
  ros::Publisher AIkit2_pub = n.advertise<sensor_msgs::Imu>("AIkit2r/imu", 10);

  //republish AIkit3 data
  ros::Subscriber AIkit3_sub = n.subscribe("aikit3/imu",10,AIkit3Callback);
  ros::Publisher AIkit3_pub = n.advertise<sensor_msgs::Imu>("AIkit3r/imu", 10);

  //republish AIkit4 data
  ros::Subscriber AIkit4_sub = n.subscribe("aikit4/imu",10,AIkit4Callback);
  ros::Publisher AIkit4_pub = n.advertise<sensor_msgs::Imu>("AIkit4r/imu", 10);

  geometry_msgs::Quaternion q1msg;
  geometry_msgs::Quaternion q2msg;
  geometry_msgs::Quaternion q3msg;
  geometry_msgs::Quaternion q4msg;

  while(n.ok()){
    sensor_msgs::Imu imu1;
    sensor_msgs::Imu imu2;
    sensor_msgs::Imu imu3;
    sensor_msgs::Imu imu4;

    tf::quaternionTFToMsg(q1,q1msg);
    tf::quaternionTFToMsg(q2,q2msg);
    tf::quaternionTFToMsg(q3,q3msg);
    tf::quaternionTFToMsg(q4,q4msg);

    //Message construction for AIkit1
    imu1.orientation = q1msg;
    imu1.orientation_covariance = {0,0,0,0,0,0,0,0,0};
    imu1.linear_acceleration = a1;
    imu1.linear_acceleration_covariance = {0,0,0,0,0,0,0,0,0};
    imu1.angular_velocity = w1;
    imu1.angular_velocity_covariance = {0,0,0,0,0,0,0,0,0};
    AIkit1_pub.publish(imu1);

    //Message construction for AIkit2
    imu2.orientation = q2msg;
    imu2.orientation_covariance = {0,0,0,0,0,0,0,0,0};
    imu2.linear_acceleration = a2;
    imu2.linear_acceleration_covariance = {0,0,0,0,0,0,0,0,0};
    imu2.angular_velocity = w2;
    imu2.angular_velocity_covariance = {0,0,0,0,0,0,0,0,0};
    AIkit2_pub.publish(imu2);

    //Message construction for AIkit3
    imu3.orientation = q3msg;
    imu3.orientation_covariance = {0,0,0,0,0,0,0,0,0};
    imu3.linear_acceleration = a3;
    imu3.linear_acceleration_covariance = {0,0,0,0,0,0,0,0,0};
    imu3.angular_velocity = w3;
    imu3.angular_velocity_covariance = {0,0,0,0,0,0,0,0,0};
    AIkit3_pub.publish(imu3);

    //Message construction for AIkit4
    imu4.orientation = q4msg;
    imu4.orientation_covariance = {0,0,0,0,0,0,0,0,0};
    imu4.linear_acceleration = a4;
    imu4.linear_acceleration_covariance = {0,0,0,0,0,0,0,0,0};
    imu4.angular_velocity = w4;
    imu4.angular_velocity_covariance = {0,0,0,0,0,0,0,0,0};
    AIkit4_pub.publish(imu4);

    ros::spinOnce();
    r.sleep();
  }
}
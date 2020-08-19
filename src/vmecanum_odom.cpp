#include <ros/ros.h>
#include <control_msgs/JointControllerState.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include <math.h>
//#include "mecanumrover.h"


float wheel_speed[4] = { 0 };
float w_rate=0.0525f;
void state0_callback(const control_msgs::JointControllerState& state_msg)
{
  wheel_speed[0] = state_msg.process_value*w_rate;
}
void state1_callback(const control_msgs::JointControllerState& state_msg)
{
  wheel_speed[1] = state_msg.process_value*w_rate;
}
void state2_callback(const control_msgs::JointControllerState& state_msg)
{
  wheel_speed[2] = state_msg.process_value*w_rate;
}
void state3_callback(const control_msgs::JointControllerState& state_msg)
{
  wheel_speed[3] = state_msg.process_value*w_rate;
}

float publish_rate = 20;

int main(int argc, char** argv)
{
  float ROVER_D=(0.266/2),ROVER_HB=(0.230/2);
  int F_L=0,F_R=1,R_L=2,R_R=3;

  ros::init(argc, argv, "s4_omni_odom");
  ros::NodeHandle n;
  ros::NodeHandle pn("~");
  // publish
  ros::Publisher odom_pub = n.advertise<geometry_msgs::Twist>("rover_odo", 10);

  // Subscribe
  ros::Subscriber odometry0 = n.subscribe("wheel0/state", 10, state0_callback);
  ros::Subscriber odometry1 = n.subscribe("wheel1/state", 10, state1_callback);
  ros::Subscriber odometry2 = n.subscribe("wheel2/state", 10, state2_callback);
  ros::Subscriber odometry3 = n.subscribe("wheel3/state", 10, state3_callback);

  pn.getParam("rover_d", ROVER_D);
  pn.getParam("rover_hb", ROVER_HB);
  pn.getParam("f_l", F_L);
  pn.getParam("f_r", F_R);
  pn.getParam("r_l", R_L);
  pn.getParam("r_r", R_R);

  float dt = 1.0 / publish_rate;
  ros::Rate loop_rate(publish_rate);

  while (ros::ok())
  {

    geometry_msgs::Twist rover_odo;

    rover_odo.linear.x  = ((wheel_speed[F_R] + wheel_speed[R_R] + -1.0*(wheel_speed[F_L] + wheel_speed[R_L]))/4.0);
    rover_odo.linear.y  = ((wheel_speed[F_R] + -1.0*wheel_speed[R_R] + wheel_speed[F_L] + -1.0*wheel_speed[R_L]))/4.0;

    double dCenter2Wheel = sqrt(ROVER_D*ROVER_D + ROVER_HB*ROVER_HB);
    rover_odo.angular.z = (atan(wheel_speed[F_L]/dCenter2Wheel) + atan(wheel_speed[F_R]/dCenter2Wheel) + atan(wheel_speed[R_L]/dCenter2Wheel) + atan(wheel_speed[R_R]/dCenter2Wheel))/4.0;

    odom_pub.publish(rover_odo);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

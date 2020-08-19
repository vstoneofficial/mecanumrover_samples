#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include <math.h>
//#include "mecanumrover.h"

geometry_msgs::Twist twist_last;
bool twist_enable;
float gain=21;

void twist_stamped_callback(const geometry_msgs::Twist& twist_msg)
{
  twist_last = twist_msg;
  twist_enable = true;
}

int main(int argc, char** argv)
{
  float ROVER_D=(0.266/2),ROVER_HB=(0.230/2);
  int F_L=0,F_R=1,R_L=2,R_R=3;

  ros::init(argc, argv, "omni_driver");
  ros::NodeHandle n;
  ros::NodeHandle pn("~");

  // publish
  ros::Publisher wheel0_pub = n.advertise<std_msgs::Float64>("wheel0", 10);
  ros::Publisher wheel1_pub = n.advertise<std_msgs::Float64>("wheel1", 10);
  ros::Publisher wheel2_pub = n.advertise<std_msgs::Float64>("wheel2", 10);
  ros::Publisher wheel3_pub = n.advertise<std_msgs::Float64>("wheel3", 10);
  // Subscribe
  ros::Subscriber joy_sub = n.subscribe("rover_twist", 10, twist_stamped_callback);

  pn.getParam("gain", gain);
  pn.getParam("rover_d", ROVER_D);
  pn.getParam("rover_hb", ROVER_HB);
  pn.getParam("f_l", F_L);
  pn.getParam("f_r", F_R);
  pn.getParam("r_l", R_L);
  pn.getParam("r_r", R_R);

  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    if (twist_enable)
    {
      std_msgs::Float64 data[4];

      float mem_com_x = twist_last.linear.x*gain;  //[m/s]
      float mem_com_y = twist_last.linear.y*gain;  //[m/s]
      float mem_com_z = twist_last.angular.z*gain;  //[rad/s]
      float dCenter2Wheel = sqrt(ROVER_D*ROVER_D + ROVER_HB*ROVER_HB);

      data[F_L].data = -1.0*(mem_com_x - dCenter2Wheel*mem_com_z - mem_com_y);
      data[F_R].data = (mem_com_x + dCenter2Wheel*mem_com_z + mem_com_y);
      data[R_L].data = -1.0*(mem_com_x - dCenter2Wheel*mem_com_z + mem_com_y);
      data[R_R].data = (mem_com_x + dCenter2Wheel*mem_com_z - mem_com_y);

      wheel0_pub.publish(data[0]);
      wheel1_pub.publish(data[1]);
      wheel2_pub.publish(data[2]);
      wheel3_pub.publish(data[3]);
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

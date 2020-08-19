#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <string>
#include <math.h>


int main(int argc, char** argv)
{
  ros::init(argc, argv, "liftup_sus");
  ros::NodeHandle n;
  ros::NodeHandle pn("~");

  // publish
  ros::Publisher pub0 = n.advertise<std_msgs::Float64>("sus0", 10);
  ros::Publisher pub1 = n.advertise<std_msgs::Float64>("sus1", 10);
  ros::Publisher pub2 = n.advertise<std_msgs::Float64>("sus2", 10);
  ros::Publisher pub3 = n.advertise<std_msgs::Float64>("sus3", 10);

  ros::Publisher pub_bumper0 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller0/command", 10);
  ros::Publisher pub_bumper1 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller1/command", 10);
  ros::Publisher pub_bumper2 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller2/command", 10);
  ros::Publisher pub_bumper3 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller3/command", 10);
  ros::Publisher pub_bumper4 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller4/command", 10);
  ros::Publisher pub_bumper5 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller5/command", 10);
  ros::Publisher pub_bumper6 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller6/command", 10);
  ros::Publisher pub_bumper7 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller7/command", 10);
  ros::Publisher pub_bumper8 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller8/command", 10);
  ros::Publisher pub_bumper9 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller9/command", 10);
  ros::Publisher pub_bumper10 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller10/command", 10);
  ros::Publisher pub_bumper11 = n.advertise<std_msgs::Float64>("/vmecanumrover/bumper_controller11/command", 10);

  ros::Publisher pub_charger = n.advertise<std_msgs::Float64>("/vmecanumrover/wyrelesscharger_controller/command", 10);

  ROS_INFO("lift up stand by(initial wait)");
  ros::Duration(1.5).sleep();
  ros::Rate loop_rate(50);
  int i=0;
  int liftup_step=100;

    std_msgs::Float64 f;
    f.data=0;

  ROS_INFO("start lift up.");
  while (ros::ok())
  {
    std_msgs::Float64 command_pos;
    command_pos.data = (liftup_step-i) * (0.02/liftup_step);
    pub0.publish(command_pos);
    pub1.publish(command_pos);
    pub2.publish(command_pos);
    pub3.publish(command_pos);
    if(command_pos.data<=0) break;
    i++;

    pub_bumper0.publish(f);
    pub_bumper1.publish(f);
    pub_bumper2.publish(f);
    pub_bumper3.publish(f);
    pub_bumper4.publish(f);
    pub_bumper5.publish(f);
    pub_bumper6.publish(f);
    pub_bumper7.publish(f);
    pub_bumper8.publish(f);
    pub_bumper9.publish(f);
    pub_bumper10.publish(f);
    pub_bumper11.publish(f);
    pub_charger.publish(f);

    ros::spinOnce();
    loop_rate.sleep();
  }
  ROS_INFO("end lift up.");

  return 0;
}


#include <ros/ros.h>
#include <control_msgs/JointControllerState.h>
#include <std_msgs/Int16MultiArray.h>
#include <string>
#include <math.h>

float sns[12] = { 0 };
const float TH = 0.0035;

void state0_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[0] = state_msg.process_value;
}
void state1_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[1] = state_msg.process_value;
}
void state2_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[2] = state_msg.process_value;
}
void state3_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[3] = state_msg.process_value;
}
void state4_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[4] = state_msg.process_value;
}
void state5_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[5] = state_msg.process_value;
}
void state6_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[6] = state_msg.process_value;
}
void state7_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[7] = state_msg.process_value;
}
void state8_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[8] = state_msg.process_value;
}
void state9_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[9] = state_msg.process_value;
}
void state10_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[10] = state_msg.process_value;
}
void state11_callback(const control_msgs::JointControllerState& state_msg)
{
  sns[11] = state_msg.process_value;
}



float publish_rate = 20;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "s4_omni_odom");
  ros::NodeHandle n;
  ros::NodeHandle pn("~");
  // publish
  ros::Publisher sensor_pub = n.advertise<std_msgs::Int16MultiArray>("rover_sensor", 10);
  // Subscribe
  ros::Subscriber sn0 = n.subscribe("sn0/state", 10, state0_callback);
  ros::Subscriber sn1 = n.subscribe("sn1/state", 10, state1_callback);
  ros::Subscriber sn2 = n.subscribe("sn2/state", 10, state2_callback);
  ros::Subscriber sn3 = n.subscribe("sn3/state", 10, state3_callback);
  ros::Subscriber sn4 = n.subscribe("sn4/state", 10, state4_callback);
  ros::Subscriber sn5 = n.subscribe("sn5/state", 10, state5_callback);
  ros::Subscriber sn6 = n.subscribe("sn6/state", 10, state6_callback);
  ros::Subscriber sn7 = n.subscribe("sn7/state", 10, state7_callback);
  ros::Subscriber sn8 = n.subscribe("sn8/state", 10, state8_callback);
  ros::Subscriber sn9 = n.subscribe("sn9/state", 10, state9_callback);
  ros::Subscriber sn10 = n.subscribe("sn10/state", 10, state10_callback);
  ros::Subscriber sn11 = n.subscribe("sn11/state", 10, state11_callback);

  float dt = 1.0 / publish_rate;
  ros::Rate loop_rate(publish_rate);

  while (ros::ok())
  {

    std_msgs::Int16MultiArray rover_sensor;
    rover_sensor.data.resize(2);

    rover_sensor.data[0] = rover_sensor.data[1] = 0;

    if(sns[0]>TH) rover_sensor.data[1] |= 0x0001;
    if(sns[1]>TH) rover_sensor.data[1] |= 0x0004;
    if(sns[2]>TH) rover_sensor.data[1] |= 0x0010;
    if(sns[3]>TH) rover_sensor.data[1] |= 0x0400;
    if(sns[4]>TH) rover_sensor.data[1] |= 0x1000;
    if(sns[5]>TH) rover_sensor.data[1] |= 0x4000;

    if(sns[6]>TH) rover_sensor.data[0] |= 0x0001;
    if(sns[7]>TH) rover_sensor.data[0] |= 0x0004;
    if(sns[8]>TH) rover_sensor.data[0] |= 0x0010;
    if(sns[9]>TH) rover_sensor.data[0] |= 0x0400;
    if(sns[10]>TH) rover_sensor.data[0] |= 0x1000;
    if(sns[11]>TH) rover_sensor.data[0] |= 0x4000;


    sensor_pub.publish(rover_sensor);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

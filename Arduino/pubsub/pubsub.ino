/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>

#define WHEELRAD 0.06 //The radius of the wheel (m)
#define WHEELDIST 0.5 //Distance between wheels (m)
volatile float wl, wr;

ros::NodeHandle  nh;


void set_wheel_speeds(float v, float w) {
  /***Equations for a differential drive mobile robot.
  * We are avoiding divisions to make it faster
  ***/
  //Right wheel angular speed [rad/s]
  wr = (2.0 * v + WHEELDIST * w) * (0.5 * WHEELRAD); //Right wheel angular speed [rad/s]
  wl = (2.0 * v - WHEELDIST * w) * (0.5 * WHEELRAD); //Left wheel angular speed [rad/s]
}

void cmd_vel_cb( const geometry_msgs::Twist& vel_msg){
  set_wheel_speeds(vel_msg.linear.x,vel_msg.angular.z);
}


ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("cmd_vel", cmd_vel_cb );

std_msgs::Float32 wr_msg,wl_msg; //right and left wheel ros message

ros::Publisher wr_pub("wr", &wr_msg);
ros::Publisher wl_pub("wl", &wl_msg);

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(wr_pub);
  nh.advertise(wl_pub);
  nh.subscribe(cmd_vel_sub);
}

void loop()
{
  if (!(millis() % 100)) {
    wr_msg.data=wr;
    wl_msg.data=wl;
    
    wr_pub.publish(&wr_msg);
    wl_pub.publish(&wl_msg);
  }
  nh.spinOnce();
}

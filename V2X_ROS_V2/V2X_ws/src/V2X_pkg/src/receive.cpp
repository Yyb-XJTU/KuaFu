#include "ros/ros.h"
#include "V2X_pkg/V2X.h"
#include "std_msgs/Int32MultiArray.h"
void chatterCallback(const V2X_pkg::V2X::ConstPtr& msg)
{
  static int count = 0;
  ROS_INFO("COUNT: %d",count);
  count++;
  ROS_INFO("------------------------------");
  // for(int i = 0;i < msg->data.size();i++)
  // {
  //   ROS_INFO("Index: %d   count: %d", msg->data[i], i);
  // }
  ROS_INFO("Yellow:");
  ROS_INFO("--------------------------");
  for(int i = 0;i < msg->Yellow.size();i++)
    ROS_INFO("Index: %d", msg->Yellow[i]);

  ROS_INFO("Red:");
  ROS_INFO("--------------------------");
  for(int i = 0;i < msg->Red.size();i++)
    ROS_INFO("Index: %d", msg->Red[i]);

  ROS_INFO("Black:");
  ROS_INFO("--------------------------");
  for(int i = 0;i < msg->Black.size();i++)
    ROS_INFO("Index: %d", msg->Black[i]);   
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "receive");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("road_pub", 1000, chatterCallback);
  ros::spin();
  return 0;
}

#include<vector>
#include<deque>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "osm2rviz/V2X.h"
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include "osm2rviz/goal_pose_subscriber.h"
#include "osm2rviz/init_pose_subscriber.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <cmath>
#include"osm2rviz/sim_car.h"
#define PI 3.1415926
using namespace std;
int main(int argc, char **argv)
{
  ros::init(argc, argv, "car2rviz");
  ros::NodeHandle n;
  ros::Rate loop_rate(8);
  sim_car car(n, "/global_guideline", "/pos", 1000);
  std_msgs::UInt16 replan;
  int clock = 0;
  while (ros::ok())
  {
    // 任务完成，发送重规划标志
    if(car.line.size()>0 && car.cnt==car.line.size())
    {
      clock = (clock + 1)%8;
      if(clock == 0)
      {
        replan.data = 1;
        car.pub_replan.publish(replan);   
        replan.data = 0;
        car.line.clear();
      }
    }

    car.pos_pub2others.publish(car.pos_msg);
    car.car_display();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
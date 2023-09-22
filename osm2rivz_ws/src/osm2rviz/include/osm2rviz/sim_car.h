#ifndef OSM2RVIZ_SIM_CAR_H
#define OSM2RVIZ_SIM_CAR_H
#include <vector>
#include <ros/ros.h>
#include "osm2rviz/Guide_line.h"
#include <visualization_msgs/Marker.h>
#include"std_msgs/Float32MultiArray.h"
#include"std_msgs/UInt16.h"
using namespace std;
class sim_car
{
public:
    sim_car(ros::NodeHandle &nh, const std::string &sub_name, const std::string &pub_name, int buff_size);
    vector<vector<float>> line;
    long long cnt = 0;
    bool task_complete = 1;
    vector<float> pos;
    vector<float> pos_Init = {497.966, 280.528, 0};
    std_msgs::Float32MultiArray pos_msg;
    
    ros::Publisher pos_pub2rviz;
    ros::Publisher pos_pub2others;

    ros::Publisher pub_replan;
    ros::Subscriber roads_sub;
    void car_display();
private:
    vector<float> temp;
    visualization_msgs::Marker pos_display;

    void MessageCallBack(const osm2rviz::Guide_line::ConstPtr &guide_line_ptr);
};
#endif
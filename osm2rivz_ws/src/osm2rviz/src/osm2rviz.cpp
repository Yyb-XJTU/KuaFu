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
struct node
{
	float x;
	float y;
};
struct way
{
	vector<int> ids;
	vector<node> nodes;
};
struct rectangle
{
  vector<float> points_x;
  vector<float> points_y;
};
class V2X_Listener
{
public:
  bool first_receive = 1;
  bool change_flag = 1;
  osm2rviz::V2X road_msg_old;
  osm2rviz::V2X road_msg;
public:
  void chatterCallback(const osm2rviz::V2X::ConstPtr& msg);

};
void readways(const std::string path, vector<way>& ways, const vector<node> &nodes);
void readnodes(const std::string path, vector<node> &nodes);
void readrectangles(const std::string path, vector<rectangle> &rectangles);
void torviz(vector<way> &ways, visualization_msgs::MarkerArray &osm_map);
void rectangles2rviz(vector<rectangle> &rectangles, visualization_msgs::MarkerArray &rectangles_);
void change_color(visualization_msgs::MarkerArray &osm_map, V2X_Listener &listener);
void V2X_Listener::chatterCallback(const osm2rviz::V2X::ConstPtr& msg)
{
  road_msg.Yellow = msg->Yellow;
  road_msg.Red = msg->Red;
  road_msg.Black = msg->Black;
  if(first_receive)
  {
    road_msg_old.Yellow = road_msg.Yellow;
    road_msg_old.Red = road_msg.Red;
    road_msg_old.Black = road_msg.Black;
    first_receive = 0;
  }
  else
  {
    if(road_msg_old.Yellow != road_msg.Yellow || 
      road_msg_old.Red != road_msg.Red || 
      road_msg_old.Black != road_msg.Black)
    {
      road_msg_old.Yellow = road_msg.Yellow;
      road_msg_old.Red = road_msg.Red;
      road_msg_old.Black = road_msg.Black;
      change_flag = 1;
    }
  }
}
int main(int argc, char **argv)
{
  // 接受V2X发送的消息
  osm2rviz::V2X road_msg;
  // 解析som数据和框框
  vector<way> ways;
  vector<node> nodes;
  vector<rectangle> rectangles;
  string path_nodes = "/home/yyb/kuafu/yyb/osm2rivz_ws/src/osm2rviz/osm_txt/nodes_true.txt";
  string path_ways = "/home/yyb/kuafu/yyb/osm2rivz_ws/src/osm2rviz/osm_txt/way_nodes.txt";
  string path_rectangles = "/home/yyb/kuafu/yyb/osm2rivz_ws/src/osm2rviz/osm_txt/rectangle.txt";
  readnodes(path_nodes, nodes);
  readways(path_ways, ways, nodes);
  readrectangles(path_rectangles, rectangles);
  // for (int id = 0; id < rectangles.size(); id++)
  // {
  //   for(int j = 0; j < 4; j++)
  //   {
  //     cout<<rectangles[id].points_x[j]<<" "<<rectangles[id].points_y[j]<<"   ";
  //   }
  //   cout<<endl;
  // }
  ros::init(argc, argv, "osm_map");
  ros::NodeHandle n;

  // 接收rviz起始点坐标
  std::shared_ptr<InitPoseSubscriber2D> init_pose_sub_ptr_;
  std::shared_ptr<GoalPoseSubscriber2D> goal_pose_sub_ptr_;
  init_pose_sub_ptr_ = std::make_shared<InitPoseSubscriber2D>(n, "/initialpose", 1);
  goal_pose_sub_ptr_ = std::make_shared<GoalPoseSubscriber2D>(n, "/goalpose", 1);
  std::deque<geometry_msgs::PoseWithCovarianceStampedPtr> init_pose_deque_;
  std::deque<geometry_msgs::PoseStampedPtr> goal_pose_deque_;
  geometry_msgs::PoseWithCovarianceStampedPtr current_init_pose_ptr_;
  geometry_msgs::PoseStampedPtr current_goal_pose_ptr_;
  float init_x;
  float init_y;
  float goal_x;
  float goal_y;
  float start_yaw;
  float goal_yaw;
  // 发送osm地图和框框
  V2X_Listener listener;
  ros::Publisher osm_map2rviz = n.advertise<visualization_msgs::MarkerArray>("osm_map", 1000);
  ros::Publisher rectangles_2rviz = n.advertise<visualization_msgs::MarkerArray>("rectangles", 1000);
  ros::Subscriber sub = n.subscribe("road_pub", 1000, &V2X_Listener::chatterCallback, &listener);
  visualization_msgs::MarkerArray osm_map;
  visualization_msgs::MarkerArray rectangles_;
  
  rectangles2rviz(rectangles, rectangles_);
  torviz(ways, osm_map);
  ros::Rate loop_rate(10);
  int count = 0;

  // // 模拟小车，沿轨迹
  // sim_car car(n, "global_guideline", "pos", 1000);

  while (ros::ok())
  {
    change_color(osm_map, listener);
    osm_map2rviz.publish(osm_map);
    rectangles_2rviz.publish(rectangles_);
    // 解析出当前起始点坐标
    init_pose_sub_ptr_->ParseData(init_pose_deque_);
    goal_pose_sub_ptr_->ParseData(goal_pose_deque_);
    while(!init_pose_deque_.empty() && !goal_pose_deque_.empty())
    {
      current_init_pose_ptr_ = init_pose_deque_.front();
      init_pose_deque_.pop_front();
      current_goal_pose_ptr_ = goal_pose_deque_.front();
      goal_pose_deque_.pop_front();
      double start_yaw = tf::getYaw(current_init_pose_ptr_->pose.pose.orientation)*180/PI;
      double goal_yaw = tf::getYaw(current_goal_pose_ptr_->pose.orientation)*180/PI;
      // 解析出当前起始点坐标
      init_x = current_init_pose_ptr_->pose.pose.position.x;
      init_y = current_init_pose_ptr_->pose.pose.position.y;
      goal_x = current_goal_pose_ptr_->pose.position.x;
      goal_y = current_goal_pose_ptr_->pose.position.y;
      cout<<"init_x:"<<init_x<<"  "<<"init_y:"<<init_y<<"start_yaw:"<<start_yaw<<endl;
      cout<<"goal_x:"<<goal_x<<"  "<<"goal_y:"<<goal_y<<"goal_yaw:"<<goal_yaw<<endl;  
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}


void readways(const std::string path, vector<way>& ways, const vector<node> &nodes)
{
  ifstream ifData(path);
  string line;
  string single;
  stringstream ss;
  way way_tmp;
  while (!ifData.eof())
  {
    line.clear();
        getline(ifData, line);
    if (line.empty())
            continue;
    ss.clear();
        ss << line;
    way_tmp.nodes.clear();
    way_tmp.ids.clear();
    while(ss >> single)
    {
      int id = atoi(single.c_str());
      way_tmp.ids.push_back(id);
      way_tmp.nodes.push_back(nodes[id-1]);
      
    }
    ways.push_back(way_tmp);
  }
}


void readnodes(const std::string path, vector<node> &nodes)
{
  ifstream ifData(path);
  string line;
  string single;
  stringstream ss;
  node node_tmp;
  	while (!ifData.eof())
    {
		line.clear();
        getline(ifData, line);
		if (line.empty())
            continue;
		ss.clear();
        ss << line;
		ss >> single;
		node_tmp.y =  atof(single.c_str());
		ss >> single;
		node_tmp.x =  atof(single.c_str());
		nodes.push_back(node_tmp);
	}
}


void readrectangles(const std::string path, vector<rectangle> &rectangles)
{
  ifstream ifData(path);
  string line;
  string single;
  stringstream ss;
  rectangle rectangle_tmp;
  while (!ifData.eof())
  {
    line.clear();
    getline(ifData, line);
    if (line.empty())
      continue;
    ss.clear();
    ss << line;
    for(int i = 0; i < 4; i++)
    {
      ss >> single;
      rectangle_tmp.points_x.push_back(atof(single.c_str()));
      // cout<<atof(single.c_str())<<" ";
      ss >> single;
      rectangle_tmp.points_y.push_back(atof(single.c_str()));
      // cout<<atof(single.c_str())<<"   ";
    }
    while(ss >> single);
    // cout<<endl;
    rectangles.push_back(rectangle_tmp);
    rectangle_tmp.points_x.clear();
    rectangle_tmp.points_y.clear();
	}
  
}


void torviz(vector<way> &ways, visualization_msgs::MarkerArray &osm_map)
{
    for (int id = 0; id < ways.size(); id++)
    {
      visualization_msgs::Marker osm_way;
      if (id == 0) {
            osm_way.action = 3;
        }
      osm_way.header.frame_id = "world";
      osm_way.header.stamp = ros::Time::now();
      osm_way.type = visualization_msgs::Marker::LINE_STRIP;
      osm_way.id = id;
      osm_way.scale.x = 0.5;
      osm_way.scale.y = 0.5;
      osm_way.scale.z = 0.1;
      osm_way.color.a = 1;

      osm_way.color.r = 1.0;
      osm_way.color.b = 1.0;
      osm_way.color.g = 1.0;
      osm_way.pose.orientation.w = 1.0;
      for(int j = 0; j < ways[id].nodes.size(); j++)
      {
        geometry_msgs::Point p;
        p.x =  ways[id].nodes[j].x;
        p.y =  ways[id].nodes[j].y;
        p.z = 0;
        osm_way.points.emplace_back(p);

      }
      osm_map.markers.emplace_back(osm_way);
    }
}


void rectangles2rviz(vector<rectangle> &rectangles, visualization_msgs::MarkerArray &rectangles_)
{
    for (int id = 0; id < rectangles.size(); id++)
    {
      visualization_msgs::Marker rectangle_;
      if (id == 0) {
            rectangle_.action = 3;
        }
      rectangle_.header.frame_id = "world";
      rectangle_.header.stamp = ros::Time::now();
      rectangle_.type = visualization_msgs::Marker::LINE_STRIP;
      rectangle_.id = id;
      rectangle_.scale.x = 0.3;
      rectangle_.scale.y = 0.3;
      rectangle_.scale.z = 0.1;
      rectangle_.color.a = 1;

      rectangle_.color.r = 0.0;
      rectangle_.color.b = 1.0;
      rectangle_.color.g = 0.0;
      rectangle_.pose.orientation.w = 1.0;
      geometry_msgs::Point p;
      for(int j = 0; j < 4; j+=2)
      {
        p.x =  rectangles[id].points_x[j];
        p.y =  rectangles[id].points_y[j];
        p.z = 0;
        rectangle_.points.emplace_back(p);
        // cout<<p.x<<" "<<p.y<<"   ";
      }
      for(int j = 3; j > 0; j-=2)
      {
        p.x =  rectangles[id].points_x[j];
        p.y =  rectangles[id].points_y[j];
        p.z = 0;
        rectangle_.points.emplace_back(p);
      }
      p.x =  rectangles[id].points_x[0];
      p.y =  rectangles[id].points_y[0];
      p.z = 0;
      // cout<<p.x<<" "<<p.y<<endl;
      rectangle_.points.emplace_back(p);
      rectangles_.markers.emplace_back(rectangle_);
    }
}


void reset_color(visualization_msgs::MarkerArray &osm_map)
{
   for(int i = 0;i < osm_map.markers.size();i++)
      {
        int id  = i;
        osm_map.markers[id].color.r = 1.0;
        osm_map.markers[id].color.b = 1.0;
        osm_map.markers[id].color.g = 1.0;
        osm_map.markers[id].scale.x = 0.5;
        osm_map.markers[id].scale.y = 0.5;
      }
}


void change_color(visualization_msgs::MarkerArray &osm_map, V2X_Listener &listener)
{
  if(listener.change_flag && !listener.first_receive)
  {
    reset_color(osm_map);
    ROS_INFO("Yellow:");
    ROS_INFO("--------------------------");
    for(int i = 0;i < listener.road_msg_old.Yellow.size();i++)
    {
      int id  = listener.road_msg_old.Yellow[i] - 1;
      osm_map.markers[id].color.r = 1.0;
      osm_map.markers[id].color.b = 0.0;
      osm_map.markers[id].color.g = 1.0;
      osm_map.markers[id].scale.x = 3;
      osm_map.markers[id].scale.y = 3;
      ROS_INFO("Index: %d", listener.road_msg_old.Yellow[i]);
    }
    ROS_INFO("Red:");
    ROS_INFO("--------------------------");
    for(int i = 0;i < listener.road_msg_old.Red.size();i++)
    {
      int id  = listener.road_msg_old.Red[i] - 1;
      osm_map.markers[id].color.r = 1.0;
      osm_map.markers[id].color.b = 0.0;
      osm_map.markers[id].color.g = 0.0;
      osm_map.markers[id].scale.x = 3;
      osm_map.markers[id].scale.y = 3;
      ROS_INFO("Index: %d", listener.road_msg_old.Red[i]);
    }
    ROS_INFO("Black:");
    ROS_INFO("--------------------------");
    for(int i = 0;i < listener.road_msg_old.Black.size();i++)
    {
      int id  = listener.road_msg_old.Black[i] - 1;
      osm_map.markers[id].color.r = 0.0;
      osm_map.markers[id].color.b = 0.0;
      osm_map.markers[id].color.g = 0.0;
      osm_map.markers[id].scale.x = 3;
      osm_map.markers[id].scale.y = 3;
      ROS_INFO("Index: %d", listener.road_msg_old.Black[i]);   
    }
    listener.change_flag = 0;
  }
}



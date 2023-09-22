#include"osm2rviz/sim_car.h"


sim_car::sim_car(ros::NodeHandle &nh, const std::string &sub_name, const std::string &pub_name, int buff_size)
{
    roads_sub = nh.subscribe(sub_name, buff_size, &sim_car::MessageCallBack, this);
    // 发送重规划标志位
    pub_replan = nh.advertise<std_msgs::UInt16>("/replan_flag", 1000);
    // 发送当前位置给rviz或者全局规划
    pos_pub2rviz = nh.advertise<visualization_msgs::Marker>("/pos_rviz", 1);
    pos_pub2others = nh.advertise<std_msgs::Float32MultiArray>(pub_name, buff_size);
    pos_msg.data = pos_Init;
}


 void sim_car::MessageCallBack(const osm2rviz::Guide_line::ConstPtr &guide_line_ptr)
 {
    vector<vector<float>> line_;
    for(int i = 0; i < guide_line_ptr->x.size(); i++)
    {
        temp.clear();
        temp.push_back(guide_line_ptr->x[i]);
        temp.push_back(guide_line_ptr->y[i]);
        temp.push_back(guide_line_ptr->heading[i]);
        ROS_INFO("x:%f", temp[0]);
        ROS_INFO("y:%f", temp[1]);
        line_.push_back(temp);
    }
    if(line != line_)
    {
        cnt = 0;
        line = line_;
    }
 }
 

 void sim_car::car_display()
 {
    pos_display.header.frame_id = "world";
    if(cnt < line.size())
    {
        pos_msg.data.clear();
        pos = line[cnt];
        pos_msg.data = pos;
        // ROS_INFO("cnt:%d", cnt);
        // ROS_INFO("x:%f", pos[0]);
        // ROS_INFO("y:%f", pos[1]);
        pos_display.header.stamp = ros::Time();
        pos_display.id = cnt;
        cnt++;
        pos_display.type = visualization_msgs::Marker::SPHERE;
        pos_display.action = visualization_msgs::Marker::ADD;
        pos_display.pose.position.x = pos[0];
        pos_display.pose.position.y = pos[1];
        pos_display.pose.position.z = 0;
        pos_display.pose.orientation.x = 0.0;
        pos_display.pose.orientation.y = 0.0;
        pos_display.pose.orientation.z = 0.0;
        pos_display.pose.orientation.w = 1.0;
        pos_display.scale.x = 12;
        pos_display.scale.y = 12;
        pos_display.scale.z = 12;
        pos_display.color.a = 1.0;
        pos_display.color.r = 1.0;
        pos_display.color.g = 0.0;
        pos_display.color.b = 0.0;
        if(cnt == line.size())
        {
            task_complete = 1;
            pos_display.lifetime = ros::Duration(2);
        }
        else
            pos_display.lifetime = ros::Duration(0.125);
        // 发送消息给
        pos_pub2rviz.publish(pos_display);
    }
 }
#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include "V2X_pkg/V2X.h"
#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
vector<int> reading_matching_result(long long road_jam);
struct Road
{
    long long road_id;
    unsigned char state_f;
    unsigned char state_r;
};
int main(int argc, char **argv)
{
  ros::init(argc, argv, "V2X_client");
  ros::NodeHandle n;
  // 分别发给osm地图，和全局规划
  ros::Publisher road_pub = n.advertise<V2X_pkg::V2X>("road_pub", 1000);
  ros::Publisher lines_pub = n.advertise<V2X_pkg::V2X>("lines_pub", 1000);
  ros::Rate loop_rate(1);
  int port_out = 12322;
  int sockfd;
  int road_num = 98;
  int getBuffer_size = 18 + road_num * 10;

  // 向服务器发送消息
  uint8_t getBuffer[getBuffer_size];
  uint8_t sendBuffer[24];

  // map<long long, vector<int>> road_jam;
  map<long long, vector<int>> road_Yellow;
  map<long long, vector<int>> road_Red;
  map<long long, vector<int>> road_Black;
  // vector<int> line_jam;
  vector<int> line_Yellow;
  vector<int> line_Red;
  vector<int> line_Black;
  memset(getBuffer, 0, getBuffer_size);
  memset(sendBuffer, 0, 24);
  string heading = "FC";

  // 获取时间戳
  char time[15];
  std::time_t rawtime;
  std::tm* timeinfo;
  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);
  std::strftime(time,15,"%Y%m%d%H%M%S",timeinfo);

  unsigned int id = 1234567;
  for(int i = 0;i < 2;i++)
      sendBuffer[i] = heading[i];
  for(int i = 0;i < 14;i++)
      sendBuffer[2+i] = time[i];
  sendBuffer[16] = ' ';
  sendBuffer[17] = 0x00;
  for(int i = 0;i < 4;i++)
      sendBuffer[18+i] = id>>(8*(3-i))& 0x000000ff;
  sendBuffer[22] = ' ';


  // 创建socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(-1==sockfd){
      return false;
      puts("Failed to create socket");
  }

  // 设置地址与端口
  struct sockaddr_in addr;
  socklen_t  addr_len=sizeof(addr);
  bzero(&addr,addr_len);
  addr.sin_family = AF_INET;       // Use IPV4
  addr.sin_port   = htons(port_out);    //
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Time out
  struct timeval tv;
  tv.tv_sec  = 0;
  tv.tv_usec = 200000;  // 200 ms
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(struct timeval));
  
  int counter = 0;
  unsigned char get_heading[2];
  unsigned char get_time[14];
  //cout<<int(getBuffer[17])<<endl;
  Road roadArray[road_num];
  V2X_pkg::V2X road_msg_old;
  V2X_pkg::V2X road_msg;
  V2X_pkg::V2X line_msg;
  bool v2x_receive_first = 1;
  bool v2x_chane_flag = 1;
  int cnt = 0;
  while(ros::ok)
  {
    printf("Sended %d\n", ++counter);
    sendto(sockfd, sendBuffer, 24, 0, (sockaddr*)&addr, addr_len);
    int sz = recvfrom(sockfd, getBuffer, getBuffer_size, 0, (sockaddr*)&addr, &addr_len);
    if (sz > 0)
    {
      // 每次受到消息前，先把数组清空（先这样吧，懒得封装了）
      road_msg.Yellow.clear();
      road_msg.Red.clear();
      road_msg.Black.clear();
      line_msg.Yellow.clear();
      line_msg.Red.clear();
      line_msg.Black.clear();
      line_Yellow.clear();
      line_Red.clear();
      line_Black.clear();
      
      road_num = getBuffer[17];
      getBuffer[sz] = 0;
      for(int i = 0;i < 2;i++)
          get_heading[i] = getBuffer[i];
      for(int i = 0;i < 14;i++)
          get_time[i] = getBuffer[2+i];
      for(int i = 0;i < road_num;i++)
      {
        for(int j = 0;j < 8;j++)
          roadArray[i].road_id = roadArray[i].road_id<<8|getBuffer[18+i*10+j];
        roadArray[i].state_f = getBuffer[18 + i*10 +8];  
        roadArray[i].state_r = getBuffer[18 + i*10 +9];
        // 找到拥堵路段
        switch(roadArray[i].state_f)
        {
          case 'Y':{
            road_msg.Yellow.push_back(i + 1);
            road_Yellow[roadArray[i].road_id] = \
            reading_matching_result(roadArray[i].road_id);
            line_Yellow.insert(line_Yellow.end(),\
            road_Yellow[roadArray[i].road_id].begin(),\
            road_Yellow[roadArray[i].road_id].end()
            );
          }break;
          case 'R':{
            road_msg.Red.push_back(i + 1);
            road_Red[roadArray[i].road_id] = \
            reading_matching_result(roadArray[i].road_id);
            line_Red.insert(line_Red.end(),\
            road_Red[roadArray[i].road_id].begin(),\
            road_Red[roadArray[i].road_id].end()
            );
          }break;
          case 'B':{
            road_msg.Black.push_back(i + 1);
            road_Black[roadArray[i].road_id] = \
            reading_matching_result(roadArray[i].road_id);
            line_Black.insert(line_Black.end(),\
            road_Black[roadArray[i].road_id].begin(),\
            road_Black[roadArray[i].road_id].end()
            );
          }break;
          default: ; break;
        }  
      }
      line_msg.Yellow = line_Yellow;
      line_msg.Red = line_Red;
      line_msg.Black = line_Black;
      road_pub.publish(road_msg);
      lines_pub.publish(line_msg);
      cnt++;
    }
    else
    {
        puts("timeout");
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  close(sockfd);
  return 0;
}

//从路段号匹配引导线号的函数
vector<int> reading_matching_result(long long road_jam)
{
	map<long long, vector<int>> road;
	vector<int>* lines_result;
	ifstream readFile;
	readFile.open("/home/yyb/kuafu/yyb/V2X_ROS_V2/V2X_ws/src/V2X_pkg/src/matching_result.txt", ios::in);
	if (readFile.is_open())
	{
		long long road_ID;
		int line_ID;
		vector<int> lines_ID;
		while(readFile >> road_ID)
		{
			lines_ID.clear();
			while(readFile >> line_ID)
			{
				if(line_ID == 0)
					break;
				lines_ID.push_back(line_ID);
			}
			road[road_ID] = lines_ID;
		}
		
	}
	else
	{
		cout << "文件打开失败！" << endl;
	}
	readFile.close();
	return road[road_jam];

}
#include<sys/select.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>

#include<fstream>
#include<string>
#include<queue>
using namespace std;
#define _64to8 0x00000000000000ff
#define _32to8 0x000000ff
int main(){
    int port_out = 12322;
    int sockfd;
    int road_num = 98;
    queue<long long> ways_ID;
    queue<char> way_statef;
    queue<char> way_stater;
    ifstream readFile;
	readFile.open("./way_state.txt", ios::in);
	if (readFile.is_open())
	{
        long long id;
        char statef;
        char stater;
		cout << "文件打开成功！" << endl;
        for(int i = 0;i < road_num;i++)
        {
            readFile>>id;
            readFile>>statef;
            readFile>>stater;
            ways_ID.push(id);
            way_statef.push(statef);
            way_stater.push(stater);
        }
	}
	else
	{
		cout << "文件打开失败！" << endl;
	}
	readFile.close();

    // 将V2X消息发回给客户端
    int sentBuffer_size = 18 + road_num * 10;
    uint8_t getBuffer[24];
    uint8_t sendBuffer[sentBuffer_size];
    string heading = "FC";

    // 获取时间戳
    char time[15];
    std::time_t rawtime;
    std::tm* timeinfo;
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(time,15,"%Y%m%d%H%M%S",timeinfo);
    char reserved_word = '$'; 

    for(int i = 0;i < 2;i++)
        sendBuffer[i] = heading[i];
    for(int i = 0;i < 14;i++)
        sendBuffer[2+i] = time[i];
    sendBuffer[16] = reserved_word;
    sendBuffer[17] = road_num&_32to8;

    //将路径信息存到sendBuffer中
    for(int i =  0;i < road_num;i++)
    {
        for(int j = 0;j < 8;j++)
            sendBuffer[18 + j + i * 10] = ways_ID.front()>>(8*(7-j))& _64to8;
        sendBuffer[18 + i*10 + 8] = way_statef.front();
        sendBuffer[18 + i*10 + 9] = way_stater.front(); 
        ways_ID.pop();
        way_statef.pop();
        way_stater.pop();
    }  

    // 创建socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1==sockfd){
        return false;
        puts("Failed to create socket");
    }

    // 设置地址与端口
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    bzero(&addr,addr_len);
    addr.sin_family = AF_INET;       // Use IPV4
    addr.sin_port = htons(port_out);    //
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
   // Time out
    struct timeval tv;
    tv.tv_sec  = 0;
    tv.tv_usec = 200000;  // 200 ms
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(struct timeval));

    // Bind 端口，用来接受之前设定的地址与端口发来的信息,作为接受一方必须bind端口，并且端口号与发送方一致
    if (bind(sockfd, (struct sockaddr*)&addr, addr_len) == -1){
        printf("Failed to bind socket on port %d\n", port_out);
        close(sockfd);
        return false;
    }
    memset(getBuffer, 0, 24);
    int counter = 0;
    unsigned char get_heading[2];
    unsigned char get_time[14];
    unsigned int get_id = 0;

    while(1){	
     // 阻塞住接受消息
        int sz = recvfrom(sockfd, getBuffer, 24, 0, (sockaddr*)&addr, &addr_len);
        if (sz > 0){
            getBuffer[sz] = 0;
            for(int i = 0;i < 2;i++)
                get_heading[i] = getBuffer[i];
            for(int i = 0;i < 14;i++)
                get_time[i] = getBuffer[2+i];
            for(int i = 0;i < 4;i++)
                get_id = get_id<<8|getBuffer[18+i];
            cout<<get_heading<<sizeof(get_heading)<<endl;
            cout<<get_time<<sizeof(get_time)<<endl;
            cout<<get_id<<endl;
            sendto(sockfd, sendBuffer, sentBuffer_size, 0, (sockaddr*)&addr, addr_len);
        }
        else{
            puts("timeout");
        }
    }
    close(sockfd);
    return 0;
}

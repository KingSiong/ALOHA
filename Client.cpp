#include "Client.h"

Client::Client(int domain, int type, int protocol, std::string s_addr, int port)
{
    // 创建socket
    fd = socket(domain, type, protocol);
    if (fd == -1)
    {
        std::cerr << "failed to creating the socket." << std::endl;
        // return -1;
    }

    // struct sockaddr_in seraddr;
    inet_pton(AF_INET, s_addr.c_str(), &seraddr.sin_addr.s_addr);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(port);

    // 连接服务器
    int ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    std::cout << "successed to connect to the server." << std::endl;
    // printf("ret:%d\n",ret);
    if (ret == -1)
    {
        std::cerr << "failed to connect to the server." << std::endl;
        // return -1;
    }
}

/*
    协议格式：(designed by 石)
        name:  \r\n
        time:  \r\n
        msg:   \r\n
*/
int Client::sendPacket(std::string name, std::string msg)
{
    const char *c_name = name.c_str();
    const char *c_msg = msg.c_str();
    char t[20] = {0}; // 时间

    // 获取时间
    time_t timep;
    time(&timep);
    struct tm *p;
    p = gmtime(&timep);
    snprintf(t, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
    char sendBuf[1024] = {0};
    sprintf(sendBuf, "%s\r\n%s\r\n%s\r\n", c_name, t, c_msg);
    int len = write(fd, sendBuf, strlen(sendBuf) + 1);
    if (len < 0) {
        std::cerr << "failed to write data." << std::endl;
        return -1;
    }
    char recv_buffer[1024] = {0};
    while (true) {
        int recv_len = read(fd, recv_buffer, sizeof(recv_buffer));
        if (recv_len > 0) {
            return 1;
        }
    }
    // printf("len:%d\n", len);
    // printf("Client send data:%s", sendBuf); 

    return 1;
}

Client::~Client(){};
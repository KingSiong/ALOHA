#include"Client.h"

Client::Client(int domain, int type, int protocol, std::string s_addr, int port){
        // 创建socket
        fd = socket(domain, type, protocol);
        if(fd == -1) {
            perror("socket");
            //return -1;
        }

        //struct sockaddr_in seraddr;
        inet_pton(AF_INET, s_addr.c_str(), &seraddr.sin_addr.s_addr);
        seraddr.sin_family = AF_INET;
        seraddr.sin_port = htons(port);

        // 连接服务器
        int ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));
        printf("Client connect ok!\n");
        //printf("ret:%d\n",ret);
        if(ret == -1){
            printf("conncet wrong!");
            perror("connect");
            //return -1;
        }

        
    }

int Client::sendPacket(std::string name,std::string msg){
    const char*c_name = name.c_str();
    const char*c_msg = msg.c_str();
    char t[20] ={0}; //时间

    //获取时间
    time_t timep;
    time(&timep);
    struct tm *p;
    p = gmtime(&timep);
    snprintf(t, 20, "%d-%d-%d %d:%d:%d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
    /*
        协议格式：
            name:  \r\n
            time:  \r\n
            msg:   \r\n 
    */
    char sendBuf[1024] = {0};
    sprintf(sendBuf,"%s\r\n%s\r\n%s\r\n",c_name,t,c_msg);
    int len=write(fd,sendBuf,strlen(sendBuf)+1);
    if(len==-1){
        printf("%s\n", strerror(errno));
    }
    printf("len:%d\n",len);
    printf("Client send data:%s",sendBuf);

    return 1;
}

Client::~Client(){};
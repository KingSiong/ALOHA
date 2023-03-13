#include "Server.h"

Server::Server(int domain, int type, int protocol, std::string s_addr, int port) {
    socket_descriptor = socket(domain, type, protocol);
    //struct sockaddr_in addr; //用于存放ip和端口
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1234);
    bind(socket_descriptor, (struct sockaddr*)&addr, sizeof(addr));
}

void Server::start() {
    int reuse = 1;
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof( reuse ) );//设置端口复用

    const int MAXLINK=5;//规定了内核应为相应套接字排队的最大连接个数
    listen(socket_descriptor,MAXLINK);

    printf("Server listen ok!\n");

    //signal(SIGINT,stopServerRunning);//when input Ctrl+C,close Server.
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof( client_address );
    int connfd = accept(socket_descriptor,(struct sockaddr*)&client_address,&client_addrlength);

    printf("recv connect from client!\n");

    if(connfd<0){
        printf("errno is %d\n",errno);
        printf("connfd wrong!\n");
        //continue;
    }

    while(true){
        //接收消息
        //sleep(3);
        char recvBuf[1024] = {0};
        //由于字节数较少，假定一次性可以读完
        // 获取客户端的数据
        //printf("ready to read data!\n");
        int num = read(connfd, recvBuf, sizeof(recvBuf));
        //printf("read data once!\n");
        //printf("Server recv data:%s",recvBuf);
        //printf("Server recv data:%s",recvBuf+strlen(recvBuf)+1);

        if(num == -1) {
            perror("read");
            exit(-1);
        } else if(num > 0) {
            printf("recv client data :\n%s\n", recvBuf);
        } else if(num == 0) {
            // 表示客户端断开连接
            printf("client closed...");
        }

        //解析消息成一个Packet包
        Packet p;
        int len = strlen(recvBuf);
        int begin=0;
        char temp[100];
        int tag=0;
        for(int i=0; i<len; i++){
            if(recvBuf[i]=='\r'){
                recvBuf[i]='\0';
                strcpy(temp,recvBuf+begin);
                if( tag==0 )p.name = temp;
                else if(tag == 1)p.time = temp;
                else if(tag == 2)p.msg = temp;
                begin += strlen(temp)+2;
                tag += 1;
            }
            
        }
        std::cout<<"Recv packet msg "<<p.msg<<" from "<<p.name<<" at time "<<p.time<<std::endl;
        packages.push_back(p);

    }
    
}

void Server::stopServerRunning(int p){
    close(socket_descriptor);
    printf("Close Server\n");
    exit(0);
}

Server::~Server() {}

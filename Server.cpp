#include "Server.h"

// #define debug

Server::Server(int domain, int type, int protocol, std::string s_addr, int port) {
    socket_fd = socket(domain, type, protocol);
    if (socket_fd < 0) {
        std::cerr << "failed to create the socket." << std::endl;
    }
    //struct sockaddr_in addr; //用于存放ip和端口
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(s_addr.c_str());
    addr.sin_port = htons(port);
    if (bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "failed to bind the socket with address." << std::endl;
    }
}

void Server::start() {
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof( reuse ) );//设置端口复用

    if (listen(socket_fd, MAX_LINK) < 0) {
        std::cerr << "failed to listen." << std::endl;
        return;
    }

    std::cout << "server is listening." << std::endl;

    //signal(SIGINT,stopServerRunning);//when input Ctrl+C,close Server.
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof( client_address );
    while (true) {
        int connect_fd = 0;
        connect_fd = accept(socket_fd, (struct sockaddr*)&client_address, &client_addrlength);
        if (connect_fd < 0) {
            std::cerr << "error occurred." << std::endl; // to do: 
            continue;
        }
        std::cout << "receive a connect from client." << std::endl; // to do: identify the client's id.
        while (true) {
            int signal = receive_package(connect_fd);
            if (signal < 0) {
                std::cerr << "failed to receive package." << std::endl;
                continue;
            } else if (signal == 0) {
                break;
            }
        }
    }
}

int Server::receive_package(int connect_fd) {
    char recv_buffer[MAX_LEN] = {0};
    //由于字节数较少，假定一次性可以读完
    // 获取客户端的数据
    int recv_len = read(connect_fd, recv_buffer, sizeof(recv_buffer));

    if(recv_len == -1) {
        std::cerr << "failed to read." << std::endl;
        return recv_len;
    } else if(recv_len > 0) {
        std::cout << "receive a data from client test: " << recv_buffer << std::endl; // to do: identify the client's id.
        if (feedback(connect_fd) < 0) {
            std::cerr << "failed to send feedback." << std::endl;
            return -1;
        }
        handle_package(recv_buffer);
    } else if(recv_len == 0) {
        // 表示客户端断开连接
        std::cout << "client closed..." << std::endl;
    }
    return recv_len;
}

int Server::feedback(int connect_fd) {
    std::string feedback_message = "ok";
    while (write(connect_fd, feedback_message.c_str(), feedback_message.size() + 1) < 0) {

    }
    return 0;
}

void Server::handle_package(char *message) {
    //解析消息成一个Packet包
    Packet p;
    int len = strlen(message);
    int begin = 0;
    char temp[100];
    int tag = 0;
    for(size_t i = 0; i < len; ++i){
        if(message[i]=='\r'){
            message[i]='\0';
            strcpy(temp, message + begin);
            if (tag == 0) p.name = temp;
            else if (tag == 1) p.time = temp;
            else if (tag == 2) p.msg = temp;
            begin += strlen(temp) + 2;
            tag += 1;
        }
    }
    std::cout<<"Recv packet msg "<<p.msg<<" from "<<p.name<<" at time "<<p.time<<std::endl;
    packages.push_back(p);
}

void Server::stopServerRunning(int p){
    close(socket_fd);
    printf("Close Server\n");
    exit(0);
}

Server::~Server() {}

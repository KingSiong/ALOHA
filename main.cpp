#include <iostream>
#include "Client.h"
#include "Server.h"


// establish the server. 
void server_establish() {

}

// wait and listen.
void server_listen() {

}

// connect with certain client.
void server_connect() {

}

// create a new package. 
void create_package() {
    
}

// establish the channel.
void channel_establish() {

}

// send package to channel.
void send_package() {

}


int main(int argc, char **argv) {
    //创建服务端和客户端
    Server server=Server();
    Client client=Client();
    //客户端发送消息
    client.sendPacket("xvmao","hello,world!");
    client.sendPacket("jingsong","hello,world!");
    client.sendPacket("sunlu","hello,world!");
    return 0;
}
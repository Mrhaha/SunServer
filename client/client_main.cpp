//
// Created by root on 3/1/23.
//
//
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>


//基本逻辑还是创建一个基本的服务器后面加入protobuf 3
int main(int argc,char*argv[]) {
    int socketFd = socket(AF_INET,SOCK_STREAM,0);
    if (socketFd < 0)
    {
        std::cout << "socket fd create error" << std::endl;
    }

    struct sockaddr_in serverSockAddr{};
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_port = htons(8001);
    serverSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    auto ret = connect(socketFd,(struct sockaddr*)&serverSockAddr,sizeof(serverSockAddr));
    if (ret < 0) {
        std::cout << "connect error" << std::endl;
    }

    char buff[100] = "hello world";
    ssize_t nWriteByte = write(socketFd,buff,sizeof(buff));
    if (nWriteByte < 0) {
        std::cout << "write error" << std::endl;
    } else {
        std::cout << "write " << nWriteByte << "bytes" << std::endl;
    }
    exit(0);
}
//
// Created by root on 3/1/23.
//
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>


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
    serverSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    auto ret = bind(socketFd,(struct sockaddr*)&serverSockAddr,sizeof(serverSockAddr));
    setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,nullptr,0);
    if (ret < 0) {
        std::cout << "bind error " << strerror(errno) <<std::endl;
    }
    ret = listen(socketFd,1000);
    if (ret < 0) {
        std::cout << "listen error " << strerror(errno) << std::endl;
    }

    struct sockaddr_in peerSockAddr{};
    socklen_t peerLen = sizeof(sizeof(peerSockAddr));
    auto peerFd = accept(socketFd, (struct sockaddr*)&peerSockAddr, &peerLen);
    if (peerFd < 0) {
        std::cout << "accept error" << strerror(errno) << std::endl;
    }

    char buff[100];
    bzero(buff,sizeof(buff));
    ssize_t nReadByte = read(peerFd,buff,sizeof(buff));
    if (nReadByte < 0) {
        std::cout << "read error" << std::endl;
    } else {
        std::cout << "read " << nReadByte << " bytes" << std::endl;
        std::cout << buff << std::endl;
    }

    exit(0);
}
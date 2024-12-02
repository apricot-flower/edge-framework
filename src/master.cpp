//
// Created by dev on 2024/11/20.
//

#include "master.h"
#include "log.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mutex>
#include <thread>
#include <iostream>

std::once_flag monitor_flag;

void createMaster(const std::string& host_s, const int port_i, const std::string& id_s, const std::string& username_s, const std::string& password_s) {
    //在这里启动连接
    masterLinker.host = host_s;
    masterLinker.port = port_i;
    masterLinker.id = id_s;
    masterLinker.username = username_s;
    masterLinker.password = password_s;
    sync();
}

static void connecting() {
    while (true) {
        int flag = masterLinker.MasterConnect();
        if (flag == 0) {
            break;
        }
        sleep(10);
    }
    
}


//连接；需要启动一个线程来处理重连，线程幂等剥离
int MasterLinker::MasterConnect() {
    //IPV4 SOCK_STREAM即指TCP
    socketClient = socket(AF_INET, SOCK_STREAM, 0);
    if (socketClient < 0) {
        LOG_DEBUG("create tcp socket failed!");
        return -1;
    }
    sockaddr_in serverAddress;
    //协议族为IPV4
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(host.c_str());
    int success = connect(socketClient, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (success < 0) {
        LOG_DEBUG("connect tcp server failed!");
        return -1;
    }
    return 0;
}

//断开连接
void MasterLinker::MasterClose() {
    //这里不仅仅是关闭
    close(socketClient);
}

//发送，考虑重发队列
void MasterLinker::MasterSend(const std::vector<char>& msg) {
    send(socketClient, msg.data(), msg.size(), 0);
}


void MasterLinker::sync() {
    std::thread readThread(syncRead, "slave_reading");
    if (readThread.joinable()) {
        readThread.join();
    }


}


void MasterLinker::syncRead() {
    while (true) {
        char buffer[256] = {0};
        int n;
        n = read(socketClient, buffer, 255);
        std::cout << "readed:" << buffer << std::endl;
        sleep(5);
    }
}
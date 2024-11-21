//
// Created by dev on 2024/11/20.
//

#ifndef MASTER_H
#define MASTER_H
#include <string>

using namespace std;


//连接tcp服务端
void link_master(const string &host, int port, const string &id, const string &username, const string &password);

#endif //MASTER_H

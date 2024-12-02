//
// Created by dev on 2024/11/20.
//

#ifndef MASTER_H
#define MASTER_H
#include <string>
#include <vector>

class MasterLinker {
    public:
        std::string host;
        int port;
        std::string id;
        std::string username;
        std::string password;
        int MasterConnect();
        void MasterClose();
        void MasterSend(const std::vector<char>& msg);
        //todo 需要一个解析完毕处理入口
    private:
        int socketClient;
        void sync();
        void syncRead();
};

MasterLinker masterLinker;


void createMaster(const std::string& host_s, const int port_i, const std::string& id_s, const std::string& username_s, const std::string& password_s);

#endif //MASTER_H

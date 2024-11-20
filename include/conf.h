//
// Created by dev on 2024/11/20.
//

#ifndef CONF_H
#define CONF_H

#include <string>
class Conf {
    public:
        std::string host;
        int port;
        std::string id;
        std::string username;
        std::string password;
};


Conf init_conf(const std::string& confPath);

#endif //CONF_H

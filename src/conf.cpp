//
// Created by dev on 2024/11/20.
//

#include "conf.h"
#include <fstream>
#include <iostream>

#include "inifile.h"

Conf init_conf(const std::string& confPath) {
    Conf conf;
    std::ifstream file(confPath);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << confPath << std::endl;
        return conf;
    }
    inifile::IniFile ini;
    ini.Load(confPath);
    ini.GetStringValue("master", "host", &conf.host);
    ini.GetIntValue("master", "port", &conf.port);
    ini.GetStringValue("master", "id", &conf.id);
    ini.GetStringValue("master", "username", &conf.username);
    ini.GetStringValue("master", "password", &conf.password);
    return conf;
}
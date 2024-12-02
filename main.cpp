//
// Created by dev on 2024/11/20.
//

#include "log.h"
#include "conf.h"
#include "master.h"

const Conf edgeConf = init_conf("./bin/conf.ini");

int main() {
    //初始化tcp连接
    createMaster(edgeConf.host, edgeConf.port, edgeConf.id, edgeConf.username, edgeConf.password);
    return 0;
}

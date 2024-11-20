//
// Created by dev on 2024/11/20.
//

#include "log.h"
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>
#include <iostream>

std::shared_ptr<spdlog::logger> init_logger() {
    std::shared_ptr<spdlog::logger> logger;
    try {
        auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/edge_log.log", 0, 0, false, 7);
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        logger = std::make_shared<spdlog::logger>("edge-framework", spdlog::sinks_init_list{daily_sink, console_sink});
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] (%s:%#) %v");
        logger->set_level(spdlog::level::debug);
        spdlog::register_logger(logger);
        spdlog::flush_every(std::chrono::seconds(5));
    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
    return logger;
}

const std::shared_ptr<spdlog::logger> global_logger = init_logger();
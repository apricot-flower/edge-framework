//
// Created by dev on 2024/11/20.
//

#ifndef LOG_H
#define LOG_H

#include <spdlog/spdlog.h>

extern const std::shared_ptr<spdlog::logger> global_logger;

std::shared_ptr<spdlog::logger> init_logger();

#define LOG_DEBUG(msg) SPDLOG_LOGGER_DEBUG(global_logger, msg)
#define LOG_INFO(msg) SPDLOG_LOGGER_INFO(global_logger, msg)
#define LOG_WARN(msg) SPDLOG_LOGGER_WARN(global_logger, msg)
#define LOG_ERROR(msg) SPDLOG_LOGGER_ERROR(global_logger, msg)
#endif //LOG_H

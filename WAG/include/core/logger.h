#pragma once
#include <pp_util.h>

PP_TENUM(loglevel);

#define LOG_ENABLE_DEBUG 1
#define LOG_ENABLE_TRACE 1

enum loglevel {
    LOGLEVEL_FATAL = 0,
    LOGLEVEL_ERROR,
    LOGLEVEL_WARN,
    LOGLEVEL_INFO,
#if LOG_ENABLE_DEBUG
    LOGLEVEL_DEBUG,
#endif
#if LOG_ENABLE_TRACE
    LOGLEVEL_TRACE
#endif
};

#define WAG_FATAL(msg, ...) waglog_(LOGLEVEL_FATAL, msg, ##__VA_ARGS__)
#define WAG_ERROR(msg, ...) waglog_(LOGLEVEL_ERROR, msg, ##__VA_ARGS__)
#define WAG_WARN(msg, ...) waglog_(LOGLEVEL_WARN, msg, ##__VA_ARGS__)
#define WAG_INFO(msg, ...) waglog_(LOGLEVEL_INFO, msg, ##__VA_ARGS__)
#if LOG_ENABLE_DEBUG
#define WAG_DEBUG(msg, ...) waglog_(LOGLEVEL_DEBUG, msg, ##__VA_ARGS__)
#else
#define WAG_DEBUG(msg, ...)
#endif
#if LOG_ENABLE_TRACE
#define WAG_TRACE(msg, ...) waglog_(LOGLEVEL_TRACE, msg, ##__VA_ARGS__)
#else
#define WAG_TRACE(msg, ...)
#endif

void waglog_(enum loglevel level, const char *msg, ...);
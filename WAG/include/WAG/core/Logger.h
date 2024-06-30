#pragma once

#include <defines.h>

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1

// Disable debug and trace logging for release builds
#if _DEBUG
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#endif

typedef enum log_level {
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR = 1,
	LOG_LEVEL_WARN = 2,
	LOG_LEVEL_INFO = 3,
	LOG_LEVEL_DEBUG = 4,
	LOG_LEVEL_TRACE = 5
} log_level;

/**
 * @brief Initializes logging system. Call twice; once with state = 0 to get required memory size,
 * then a second time passing allocated memory to state.
 * 
 * @param memory_requirement A pointer to hold the required memory size of internal state. 
 * @param state 0 if just requesting memory erquirement, otherwise allocated block of memory.
 * @return bool true on success; otherwise false.
*/
void LoggerInitialize(void* block, uint64_t* memory_requirement);
void LoggerShutdown();

void log_output(log_level level, const char* message, ...);

/// Logs a fatal-level message
#define WAGFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef WAGERROR
/// Logs a error-level message
#define WAGERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
/// Logs a warning-level message
#define WAGWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
/// Does nothing if LOG_WARN_ENABLED != 1
#define WAGWARN(mwssage, ...);
#endif
#if LOG_INFO_ENABLED == 1
/// Logs a info-level message
#define WAGINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
/// Does nothing if LOG_DEBUG_ENABLED != 1
#define WAGDEBUG(mwssage, ...);
#endif
#if LOG_DEBUG_ENABLED == 1
/// Logs a debug-level message
#define WAGDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
/// Does nothing if LOG_DEBUG_ENABLED != 1
#define WAGDEBUG(mwssage, ...);
#endif
#if LOG_TRACE_ENABLED == 1
/// Logs a trace-level message
#define WAGTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
/// Does nothing if LOG_TRACE_ENABLED != 1
#define WAGTRACE(mwssage, ...);
#endif
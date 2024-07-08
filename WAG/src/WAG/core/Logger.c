#include <WAG/core/Logger.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void _putchar(char character) {
	putc(character, stdout);
}

//TODO: Write the log data to the file
static void console_write(const char* message, uint8_t colour);
static void console_write_error(const char* message, uint8_t colour);

typedef struct LoggerInternalData {
 	FILE* log_file;
} LoggerInternalData;

static LoggerInternalData* logger = NULL;
bool LoggerInitialize(void* block, uint64_t* memory_requirement) {
	assert(logger == NULL && "Attempted to initialize logger twice");
	if(block == NULL) {
		*memory_requirement = sizeof(LoggerInternalData);
		return true;
	}
	memset(block, 0, sizeof(LoggerInternalData));
	logger = (LoggerInternalData*)block;
	return true;
}

void LoggerShutdown() {
	logger = NULL;
}

// Windows platform layer.
#ifdef PLATFORM_WINDOWS
#include <Windows.h>

static void console_write(const char* message, uint8_t colour) {
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	static uint8_t levels[6] = {64, 4, 6, 2, 1, 8};
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	SetConsoleTextAttribute(console_handle, levels[colour]);
	OutputDebugStringA(message);
	uint64_t length = strlen(message);
	LPDWORD number_written = 0;
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
	SetConsoleTextAttribute(console_handle, csbi.wAttributes);
}

static void console_write_error(const char* message, uint8_t colour) {
	HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
	// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	static uint8_t levels[6] = {64, 4, 6, 2, 1, 8};
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	SetConsoleTextAttribute(console_handle, levels[colour]);
	OutputDebugStringA(message);
	uint64_t length = strlen(message);
	LPDWORD number_written = 0;
	WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);
	SetConsoleTextAttribute(console_handle, csbi.wAttributes);
}
#endif

#ifdef PLATFORM_LINUX
#include <xcb/xcb.h>

static void console_write(const char* message, uint8_t colour) {
	// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
	printf("\033[%sm%s\033[0m", colour_strings[colour], message);
}

static void console_write_error(const char* message, uint8_t colour) {
	// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
	printf("\033[%sm%s\033[0m", colour_strings[colour], message);
}
#endif

#ifdef PLATFORM_APPLE

static void console_write_file(FILE* file, const char* message, uint8_t colour) {
	// Colours: FATAL, ERROR, WARN, INFO, DEBUG, TRACE.
	const char* colour_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
	fprintf(file, "\033[%sm%s\033[0m", colour_strings[colour], message);
}

static void console_write(const char* message, uint8_t colour) {
	console_write_file(stdout, message, colour);
}

static void console_write_error(const char* message, uint8_t colour) {
	console_write_file(stderr, message, colour);
}
#endif

#ifndef __builtin_va_list
#define __builtin_va_list va_list
#endif

void log_output(log_level level, const char* message, ...) {
	const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
	bool is_error = level < LOG_LEVEL_WARN;

	// Technically imposes a 32k character limit on a single log entry, but...
	// DON'T DO THAT!
	#define msg_length 32000
	char va_message[msg_length];
	char out_message[msg_length];
	memset(va_message, 0, sizeof(va_message));

	// Format original message.
	// NOTE: Oddly enough, MS's headers override the GCC/Clang va_list type with a "typedef char* va_list" in some
	// cases, and as a result throws a strange error here. The workaround for now is to just use __builtin_va_list,
	// which is the type GCC/Clang's va_start expects.
	__builtin_va_list arg_ptr;
	va_start(arg_ptr, message);
	vsnprintf(va_message, msg_length, message, arg_ptr);
	va_end(arg_ptr);

	
	sprintf(out_message, "%s%s\n", level_strings[level], va_message);

	// Platform-specific output.
	if (is_error) {
		console_write_error(out_message, level);
	} else {
		console_write(out_message, level);
	}
}
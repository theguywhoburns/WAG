/*
#pragma once

#include <defines.h>


typedef enum FILE_MODE {
	FILE_MODE_READ = 0b0000,
	FILE_MODE_WRITE = 0b0001,
	FILE_MODE_APPEND = 0b0010
} FILE_MODE;

WAG_API bool FileExists(const char* path);

WAG_API struct FILE* OpenFile(const char* path, int file_mode);

WAG_API void CloseFile(struct FILE* file);
WAG_API int32_t GetFileSize(struct FILE* file);
*/
/*
#include <WAG/util/filesystem.h>
#include <stdio.h>
#include <stdint.h>
#if defined(PLATFORM_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
#include <sys/stat.h>
#endif
bool FileExists(const char* path){
    #if defined(PLATFORM_WINDOWS)
    DWORD dwAttrib = GetFileAttributes(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    #elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
    struct stat buffer;
    return (stat(path, &buffer) == 0);
    #endif
}

struct _iobuf* __OpenFile__(const char* path, const char* mode ) {
    FILE* file = NULL;
    file = fopen(path, mode); // FUCKING AUTOCOMPLETE SUGGESTED _S BULLSHIT
    return file; // In case there is an error it would return null anyway
}

void CloseFile(struct FILE* file) {
    if(file) fclose(file);
}

int32_t GetFileSize(struct FILE* file) {
    if(!file) {return -1;}
    fseek(file, 0, SEEK_END);
    int32_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}
*/
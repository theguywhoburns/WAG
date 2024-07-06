#pragma once

#include <defines.h>

typedef struct DynamicLibrary {
	void* handle;
} DynamicLibrary;

DynamicLibrary DynamicLibraryCreate(const char* path);
void DynamicLibraryDestroy(DynamicLibrary* library);

#define DynamicLibraryGetFunction(handle, name, type) (type)__DynamicLibraryGetFunction(handle, name)
void* __DynamicLibraryGetFunction(DynamicLibrary* lib, const char* name);
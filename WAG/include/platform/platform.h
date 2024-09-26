#pragma once

#include <pp_util.h>

bool PlatformInitialize(void* block, size_t* size);
void PlatformShutdown();
bool PlatformUpdate();
void*PlatformAllocate(size_t size);
void PlatformFree(void* ptr);
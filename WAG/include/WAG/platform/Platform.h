#pragma once

#include <defines.h>
#include <WAG/core/Application.h>

// There is no window handle cause platform will contain it

// Platform specific so we shadow declare it and keep it's pointer
typedef struct PlatformInternalData PlatformInternalData;

bool PlatformInitialize(ApplicationCreationInfo* info, void* block, uint64_t* size);
bool PlatformUpdate();
void PlatformShutdown();

void* PlatformAllocate(size_t size, bool align);
void  PlatformFree(void* block);
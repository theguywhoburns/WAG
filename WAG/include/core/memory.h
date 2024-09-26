#pragma once

#include <pp_util.h>

enum MEMORY_TAG {
    MEMORY_TAG_UNKOWN = 0, // Currently unused
    MEMORY_TAG_MAX
};

bool MemorySubsystemInitialize(void* block, size_t* size);

void* wagalloc(size_t size, enum MEMORY_TAG tag);
void* wagallocex(size_t size, enum MEMORY_TAG tag, void (*dtor)(void*));
void  wagfree(void* ptr, enum MEMORY_TAG tag);
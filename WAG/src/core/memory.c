#include <core/memory.h>
#include <core/logger.h>
#include <platform/platform.h>

#include <util/allocation_map.h>

typedef struct MemorySubsystemInternals {
    AllocationMap allocation_maps[MEMORY_TAG_MAX]; // Maps
} MemorySubsystemInternals;

static MemorySubsystemInternals* memory_internals = NULL; 

bool MemorySubsystemInitialize(void* block, size_t* size) {
    if(block == NULL && size == NULL) {
        // TODO: Error log
        return false;
    } 
    *size = sizeof(MemorySubsystemInternals);
    if(block == NULL) return true;
    memory_internals = block;
    // TODO: Initialize hashtable
    return true;
}

void* wagalloc(size_t size, enum MEMORY_TAG tag) {
    void* block = PlatformAllocate(size);
    if(!memory_internals) return block;
    memory_internals->allocation_maps[tag].insert(&memory_internals->allocation_maps[tag], block, size, NULL);
    return block;
}

void* wagallocex(size_t size, enum MEMORY_TAG tag, void (*dtor)(void*)) {
    void* block = PlatformAllocate(size);
    if(!memory_internals) return block;
    memory_internals->allocation_maps[tag].insert(&memory_internals->allocation_maps[tag], block, size, dtor);
    return block;
}

void wagfree(void* ptr, enum MEMORY_TAG tag) {
    if(!ptr) return;
    PlatformFree(ptr);
    if(!memory_internals) return;
    struct AllocKVP* block = memory_internals->allocation_maps[tag].lookup(&memory_internals->allocation_maps[tag], ptr);
    if(!block) return;
    if(block->dtor) block->dtor(ptr);
    memory_internals->allocation_maps[tag].remove(&memory_internals->allocation_maps[tag], ptr);
}
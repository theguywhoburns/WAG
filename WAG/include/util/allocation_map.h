#pragma once
#include <pp_util.h>

typedef struct AllocationMap {
    struct AllocKVP {void* key; size_t size; void (*dtor)(void*);} *data;
    size_t data_capacity;
    size_t data_length; // To count total allocations per tag
    void (*insert)(struct AllocationMap*, void*, size_t, void (*dtor)(void*));
    struct AllocKVP* (*lookup)(struct AllocationMap*, void*);
    void (*remove)(struct AllocationMap*, void*);
} AllocationMap;

AllocationMap AllocationMap_new();
void AllocationMap_insert(AllocationMap* map, void* addr, size_t size, void (*dtor)(void*));
void AllocationMap_remove(AllocationMap* map, void* addr);
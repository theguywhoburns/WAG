#pragma once

#include <pp_util.h>

PP_TSTRUCT(heap_allocator);
struct heap_allocator {
    size_t allocated;
    size_t capacity;
    void* data;
    bool own; // If it owns the data
};

bool heap_allocator_new(heap_allocator* heap, size_t capacity, bool own, void* data);
void heap_allocator_free(heap_allocator* heap);
#include <util/heap_alloc.h>
#include <core/logger.h>
#include <core/memory.h>

bool heap_allocator_new(heap_allocator* heap, size_t capacity, bool own, void* data) {
    if(!own && !data) {
        WAG_ERROR("Tried to create a heap allocator with data set to NULL");
        return false;
    }
    if(capacity == 0) {
        WAG_ERROR("Tried to create a heap allocator with capacity set to 0");
        return false;
    }
    *heap = (heap_allocator){0};
    if(own) {
        heap->data = data;
        heap->own = false;
    } else {
        heap->data = (void*)wagalloc(capacity, MEMORY_TAG_UNKOWN);
        heap->own = true;
    }
    heap->allocated = 0;
    heap->capacity = capacity;

}
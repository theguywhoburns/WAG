#include <WAG/core/FlatAllocator.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/Logger.h>

FlatAllocator* FlatAllocatorCreate(void* ptr, size_t size) {
	FlatAllocator* allocator = (FlatAllocator*)walloc(sizeof(FlatAllocator), MEMORY_PREALLOCATOR);
	*allocator = (FlatAllocator){0};
	
	if(ptr == NULL) { allocator->ptr = walloc(size, MEMORY_PREALLOCATOR); allocator->own = true; }
	else allocator->ptr = ptr;
	allocator->size = size;
	return allocator;
}

void* FlatAllocatorAlloc(FlatAllocator* allocator, size_t size) {
	if(allocator->allocated + size > allocator->size) {
		WAGERROR("FlatAllocatorAlloc: Tried to allocate %d bytes, but only %d bytes are available", size, allocator->size - allocator->allocated);
		return NULL;
	}

	allocator->allocated += size;
	return (void*)((uint64_t)allocator->ptr + allocator->allocated - size);
}

void* FlatAllocatorCalloc(FlatAllocator* allocator, size_t count, size_t size) {
	return FlatAllocatorAlloc(allocator, count * size);
}

void  FlatAllocatorClear(FlatAllocator* allocator) {
	allocator->allocated = 0;
}

void  FlatAllocatorDestroy(FlatAllocator* allocator) {
	if(allocator->own) wfree(allocator->ptr, allocator->size, MEMORY_PREALLOCATOR);
	wfree(allocator, sizeof(FlatAllocator), MEMORY_PREALLOCATOR);
}

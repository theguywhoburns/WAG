#pragma once

#include <defines.h>

typedef struct FlatAllocator {
	void* ptr;
	size_t size;
	size_t allocated;
	bool own;
} FlatAllocator;

/// @brief Creates a pre-allocated memory block
/// @param ptr Pointer to the memory block set to NULL if own is false
/// @param size Size of the memory block
/// @param own If true, the memory block will be freed when the FlatAllocator is destroyed
WAG_API FlatAllocator* FlatAllocatorCreate(void* ptr, size_t size, bool own);
WAG_API void* FlatAllocatorAlloc(FlatAllocator* allocator, size_t size);
WAG_API void* FlatAllocatorCalloc(FlatAllocator* allocator, size_t count, size_t size);
WAG_API void  FlatAllocatorClear(FlatAllocator* allocator);
WAG_API void  FlatAllocatorDestroy(FlatAllocator* allocator);
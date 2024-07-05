#pragma once

#include <defines.h>

typedef enum _MEMORY_TYPE {
	MEMORY_APPLICATION = 0,
	MEMORY_ENGINE = 1,
	MEMORY_RENDERER = 2,
	MEMORY_PREALLOCATOR = 3,
	MEMORY_TINYVEC = 4,
	MEMORY_UNKNOWN = 5,
	MEMORY_NO_AUTO_DEALLOC = 6,
#if _DEBUG
	MEMORY_MAX // For debug memory usage logging
#endif
} MEMORY_TYPE;

void wmem_init(void* block, uint64_t* size);
void wmem_shutdown();

// TODO: For testing purposes these functions are exported, so get rid of them in the future
WAG_API void* walloc(size_t size, MEMORY_TYPE type);
WAG_API void* wcalloc(size_t count, size_t size, MEMORY_TYPE type);
WAG_API void  wfree(void* ptr, size_t size, MEMORY_TYPE type);

WAG_API void* walloc_ext(size_t size, MEMORY_TYPE type, void (*dtor)(void* block));
WAG_API void* wcalloc_ext(size_t size, size_t count, MEMORY_TYPE type, void (*dtor)(void* block));

//TODO: Debug and temp functions
void   __mem_add_value(MEMORY_TYPE type, void* addr, size_t value);
void   __mem_sub_value(MEMORY_TYPE type, void* addr, size_t value);
size_t __mem_get_value(MEMORY_TYPE type, void* addr);
#if _DEBUG
void __print_allocation_map();
#endif
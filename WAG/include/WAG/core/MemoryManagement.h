#pragma once

#include <defines.h>

typedef enum _MEMORY_TYPE {
	MEMORY_APPLICATION = 0,
	MEMORY_ENGINE = 1,
	MEMORY_RENDERER = 2,
	MEMORY_PREALLOCATOR = 3,
	MEMORY_UNKNOWN = 4,
#if _DEBUG
	MEMORY_MAX // For debug memory usage logging
#endif
} MEMORY_TYPE;

void wmem_init(void* block, uint64_t* size);

WAG_API void* walloc(size_t size, MEMORY_TYPE type);
WAG_API void* wcalloc(size_t count, size_t size, MEMORY_TYPE type);
WAG_API void  wfree(void* ptr, MEMORY_TYPE type);

WAG_API void* walloc_ext(size_t size, MEMORY_TYPE type, void (*dtor)(void* block));
WAG_API void* wcalloc_ext(size_t size, MEMORY_TYPE type, void (*dtor)(void* block));

#include <WAG/platform/Platform.h>
#include <WAG/core/MemoryManagement.h>
#include <string.h>
#if _DEBUG

#endif

typedef struct MemInternalData {
	uint64_t alloc_arr[MEMORY_MAX];
} MemInternalData;

static MemInternalData* mem = NULL;

void wmem_init(void* block, uint64_t* size) {
	if(block == NULL) {
		*size = sizeof(MemInternalData);
		return;
	}
	assert(mem == NULL && "Attempted to initialize memory twice");
	memset(block, 0, sizeof(MemInternalData));
	mem = (MemInternalData*)block;
}

void* walloc(size_t size, MEMORY_TYPE type) {
	return walloc_ext(size, type, NULL);
}

void* wcalloc(size_t count, size_t size, MEMORY_TYPE type) {
	return wcalloc_ext(count, size, type, NULL);
}

void  wfree(void* ptr, MEMORY_TYPE type) {
	uintptr_t address = (uintptr_t)ptr - sizeof(uintptr_t);
	if(*(uintptr_t*)address != NULL) {
		((void(*)(void*))address)(ptr);
	}
	free(address);
}

void* walloc_ext(size_t size, MEMORY_TYPE type, void (*dtor)(void* block)) {
	size += sizeof(uintptr_t);
	uintptr_t address = (uintptr_t)PlatformAllocate(size, false);
	*(uintptr_t*)address = (uintptr_t)dtor;
	return (void*)(address + sizeof(uintptr_t));
}

void* wcalloc_ext(size_t size, size_t count, MEMORY_TYPE type, void (*dtor)(void* block)) {
	size += sizeof(uintptr_t);
	uintptr_t address = (uintptr_t)PlatformAllocate(size * count, false);
	*(uintptr_t*)address = (uintptr_t)dtor;
	return (void*)(address + sizeof(uintptr_t));
}

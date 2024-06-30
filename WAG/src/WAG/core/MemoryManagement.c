#include <WAG/platform/Platform.h>
#include <WAG/core/MemoryManagement.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef struct MemInternalData {
	uint64_t alloc_arr[MEMORY_MAX];
} MemInternalData;

// I was talking about this 
static MemInternalData* mem = NULL; // <---

void wmem_init(void* block, uint64_t* size) {
	if(block == NULL) {
		*size = sizeof(MemInternalData);
		return;
	}
	assert(mem == NULL && "Attempted to initialize memory twice");
	// TODO: _D_CRT_SECURE_NO_WARNINGS in CMakeLists.txt
	memset(block, 0, sizeof(MemInternalData));
	mem = (MemInternalData*)block;
}

void wmem_shutdown() {
	mem = NULL;
}

void* walloc(size_t size, MEMORY_TYPE type) {
	return walloc_ext(size, type, NULL);
}

void* wcalloc(size_t count, size_t size, MEMORY_TYPE type) {
	return wcalloc_ext(size, count, type, NULL);
}

void  wfree(void* ptr, size_t size, MEMORY_TYPE type) {
	uintptr_t address = (uintptr_t)ptr - sizeof(uintptr_t);
	if(*(uintptr_t*)address != 0) {
		((void(*)(void*))address)(ptr);
	}
	if(mem) {
		mem->alloc_arr[type]-=size;
	}
	free((void*)address);
}

void* walloc_ext(size_t size, MEMORY_TYPE type, void (*dtor)(void* block)) {
	size += sizeof(uintptr_t);
	uintptr_t address = (uintptr_t)PlatformAllocate(size, false);
	*(uintptr_t*)address = (uintptr_t)dtor;
	if(mem) {
		mem->alloc_arr[type]+=size;
	}
	return (void*)(address + sizeof(uintptr_t));
}

void* wcalloc_ext(size_t size, size_t count, MEMORY_TYPE type, void (*dtor)(void* block)) {
	size += sizeof(uintptr_t);
	uintptr_t address = (uintptr_t)PlatformAllocate(size * count, false);
	*(uintptr_t*)address = (uintptr_t)dtor;
	if(mem) {
		mem->alloc_arr[type]+=size;
	}
	return (void*)(address + sizeof(uintptr_t));
}

void __mem_add_value(MEMORY_TYPE type, size_t value) {
	if(mem) {
		mem->alloc_arr[type]+=value;
	}
}

void __mem_sub_value(MEMORY_TYPE type, size_t value) {
	if(mem) {
		mem->alloc_arr[type]-=value;
	}
}

#if _DEBUG

#include <stdio.h>

const char* mem_type_str[MEMORY_MAX] = {
	"APP:      ",
	"ENGINE:   ",
	"RENDERER: ",
	"PREALLOC: ",
	"TINYVEC:  ",
	"UNKNOWN:  "
};

void __mem_dump() {
	if(mem) {
		printf("Memory dump:\n");
		for(int i = 0; i < MEMORY_MAX; i++) {
			printf("Type %s: %llu\n", mem_type_str[i], mem->alloc_arr[i]);
		}
	}
}

#endif
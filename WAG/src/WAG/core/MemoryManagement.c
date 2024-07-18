#include <WAG/platform/Platform.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/Logger.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#if _DEBUG
#include <WAG/util/ht.h>

typedef size_t wmem_debug_size_t;

wmem_debug_size_t wmem_debug_size_t_copy(wmem_debug_size_t a) {
	return a;
}

void wmem_debug_size_t_ht_dtor(wmem_debug_size_t a) {
	// Do nothing
}

size_t wmem_debug_size_t_ht_hash(wmem_debug_size_t a) {
	size_t ret = 0;
	__HASHFUNC_FNV1A(ret, &a, sizeof(wmem_debug_size_t));
	return ret;
}

bool wmem_debug_size_t_ht_equal(wmem_debug_size_t a, wmem_debug_size_t b) {
	return a == b;
}

define_ht_all(wmem_debug_size_t, wmem_debug_size_t);
define_ht_all_impl(wmem_debug_size_t, wmem_debug_size_t);
#endif 

typedef struct MemInternalData {
	#if _DEBUG
	wmem_debug_size_t_wmem_debug_size_t_ht_t allocation_map[MEMORY_MAX];
	#else 
	uint64_t alloc_arr[MEMORY_MAX];
	#endif
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
#if _DEBUG
	for(size_t i = 0; i < MEMORY_MAX; i++) {
		mem->allocation_map[i] = wmem_debug_size_t_wmem_debug_size_t_ht_create_ex(1000, 0.75);
	}
#else
	memset(mem->alloc_arr, 0, sizeof(mem->alloc_arr));
#endif
}

void wmem_shutdown() {
	#if _DEBUG
	for(size_t i = 0; i < MEMORY_MAX; i++) {
		wmem_debug_size_t_wmem_debug_size_t_ht_destroy(&mem->allocation_map[i]);
	}
	#endif
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
	void* _addr_ptr = (void*)address;
	if(*(uintptr_t*)address != 0) {
		((void(*)(void*))address)(ptr);
	}
	#if _DEBUG
	if(mem != NULL) {
	wmem_debug_size_t_wmem_debug_size_t_ht_remove(&mem->allocation_map[type], address);
	}
	#else
	if(mem != NULL) {
		mem->alloc_arr[type]-=size;
	}
	#endif
	// So (here exception is being thrown? the debugger tells me hat there is an exception here thrown by os, so basically yeah) it crashes here :/
	/*
		adress that i'm freeing: 0x000001f830ef0000
		but error is:
		Exception has occurred: W32/0xC0000005
		Unhandled exception at 0x00007FF847F7C55C (ucrtbased.dll) in TestBed.exe: 0xC0000005: Access violation reading location 0x000001F830EEFFF8.
	*/
	/*
		also here's the current allocation map for tinyvec
		[DEBUG]: 	Address: 000001F830FA0000, size: 40
		[DEBUG]: 	Address: 000001F830F00000, size: 40
		[DEBUG]: 	Address: 000001F830F30000, size: 40
		[DEBUG]: 	Address: 000001F830F90000, size: 40
		[DEBUG]: 	Address: 000001F830F20000, size: 40
		[DEBUG]: 	Address: 000001F830F80000, size: 40
		[DEBUG]: 	Address: 000001F830F40000, size: 40
		[DEBUG]: 	Address: 000001F830EF0000, size: 40
		[DEBUG]: 	Address: 000001F830F60000, size: 40
		[DEBUG]: 	Address: 000001F830F70000, size: 40
		[DEBUG]: 	Address: 000001F830F50000, size: 40
		[DEBUG]: 	Address: 000001F830F10000, size: 40
	*/
// Testing
	PlatformFree((void*)address);
}

void* walloc_ext(size_t size, MEMORY_TYPE type, void (*dtor)(void* block)) {
	size += sizeof(uintptr_t);
	uintptr_t address = (uintptr_t)PlatformAllocate(size, false);
	*((uintptr_t*)address) = (uintptr_t)dtor;
	#if _DEBUG
	if(mem != NULL) {
	wmem_debug_size_t_wmem_debug_size_t_ht_set(&mem->allocation_map[type], address, size);
	}
	#else
	if(mem != NULL) {
		mem->alloc_arr[type]+=size;
	}
	#endif
	return (void*)(address + sizeof(uintptr_t));
}

void* wcalloc_ext(size_t size, size_t count, MEMORY_TYPE type, void (*dtor)(void* block)) {
	size += sizeof(uintptr_t);
	uintptr_t address = (uintptr_t)PlatformAllocate(size * count, false);
	*((uintptr_t*)address) = (uintptr_t)dtor;
	#if _DEBUG
	if(mem != NULL) {
	wmem_debug_size_t_wmem_debug_size_t_ht_set(&mem->allocation_map[type], address, size * count);
	}
	#else
	if(mem != NULL) {
		mem->alloc_arr[type]+=size;
	}
	#endif
	return (void*)(address + sizeof(uintptr_t));
}

void __mem_add_value(MEMORY_TYPE type, void* addr, size_t value) {
	#if _DEBUG
	if(mem != NULL) {
	wmem_debug_size_t_wmem_debug_size_t_ht_set(&mem->allocation_map[type], (size_t)addr, value);
	}
	#else
	if(mem != NULL) {
		mem->alloc_arr[type]+=value;
	}
	#endif
}

void __mem_sub_value(MEMORY_TYPE type, void* addr, size_t value) {
	#if _DEBUG
	if(mem != NULL) {
	wmem_debug_size_t_wmem_debug_size_t_ht_remove(&mem->allocation_map[type], (size_t)addr);
	}
	#else
	if(mem != NULL) {
		mem->alloc_arr[type]-=value;
	}
	#endif
}

size_t __mem_get_value(MEMORY_TYPE type, void* addr) {
	#if _DEBUG
	if(mem != NULL) {
	return wmem_debug_size_t_wmem_debug_size_t_ht_get(&mem->allocation_map[type], (size_t)addr);
	}
	#else
	if(mem != NULL) {
		return mem->alloc_arr[type];
	}
	#endif
	return 0;
}

#if _DEBUG

const char* memory_type[MEMORY_MAX] = {
	"APPLICATION",
	"ENGINE",
	"RENDERER",
	"PREALLOCATOR",
	"TINYVEC",
	"UNKNOWN",
	"MEMNODEALLOC"
};

void __print_allocation_map() {
	for(size_t i = 0; i < MEMORY_MAX; i++) {	
		WAGDEBUG("Allocation map for %s", memory_type[i]);
		WAGDEBUG("------------------------------------");
		size_t allocated_total = 0;
		ht_foreach(mem->allocation_map[i], cur, j, wmem_debug_size_t, wmem_debug_size_t) 
		WAGDEBUG("Address: 0x%p, size: %d", cur->key, cur->val);
		allocated_total += cur->val;
		ht_foreach_end;
		if(allocated_total == 0) {WAGDEBUG("WoW Such Empty!");}
		else {WAGDEBUG("Totally allocated: %d", allocated_total);}
		WAGDEBUG("------------------------------------");
	}
}
#endif
#include <util/allocation_map.h>
#include <stdlib.h>
AllocationMap AllocationMap_new() {
    AllocationMap map = {0};
    // Default allocation capacity
    map.data = malloc(sizeof(struct AllocKVP) * 10000); // HACK: The allocation map is not managed by memory subsystem
    map.data_capacity = 10000;

}

size_t AllocationMap_hash(void* addr, size_t allocation_map_capacity) {
    
}

void AllocationMap_insert(AllocationMap* map, void* addr, size_t size, void (*dtor)(void*)) {

}

void AllocationMap_remove(AllocationMap* map, void* addr) {

}

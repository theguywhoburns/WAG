#include <WAG/util/tinyvec.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/Logger.h>
#include <string.h>

void* _tinyvec_create(uint64_t length, uint64_t stride) {
	uint64_t header_size = TINYVEC_FIELD_LENGTH * sizeof(uint64_t);
	uint64_t array_size = length * stride;
	uint64_t* new_array = walloc(header_size + array_size, MEMORY_TINYVEC);
	memset(new_array, 0, header_size + array_size);
	new_array[TINYVEC_CAPACITY] = length;
	new_array[TINYVEC_LENGTH] = 0;
	new_array[TINYVEC_STRIDE] = stride;
	return (void*)(new_array + TINYVEC_FIELD_LENGTH);
}

void _tinyvec_destroy(void* array) {
	if(!array) return;
	uint64_t* header = (uint64_t*) array - TINYVEC_FIELD_LENGTH;
		uint64_t length = header[TINYVEC_LENGTH];
		uint64_t stride = header[TINYVEC_STRIDE];
		uint64_t array_size = length * stride;
	wfree(header, sizeof(uint64_t) * TINYVEC_FIELD_LENGTH + array_size, MEMORY_TINYVEC);
}

uint64_t _tinyvec_field_get(void* array, uint64_t field) {
	uint64_t* header = (uint64_t*) array - TINYVEC_FIELD_LENGTH;
	return header[field];
}

void _tinyvec_field_set(void* array, uint64_t field, uint64_t value) {
	uint64_t* header = (uint64_t*) array - TINYVEC_FIELD_LENGTH;
	header[field] = value;
}

void* _tinyvec_resize(void* tinyvec, uint64_t size) {
	uint64_t length = _tinyvec_field_get(tinyvec, TINYVEC_LENGTH);
	uint64_t stride = _tinyvec_field_get(tinyvec, TINYVEC_STRIDE);
	void* temp = _tinyvec_create(size, stride);
	memcpy(temp, tinyvec, size * stride);
	_tinyvec_field_set(temp, TINYVEC_LENGTH, length);
	_tinyvec_destroy(tinyvec);
	return temp;
}

void* _tinyvec_reserve(void* tinyvec, uint64_t size) {
	uint64_t length = _tinyvec_field_get(tinyvec, TINYVEC_LENGTH);
	uint64_t stride = _tinyvec_field_get(tinyvec, TINYVEC_STRIDE);
	void* temp = _tinyvec_create((_tinyvec_field_get(tinyvec, TINYVEC_CAPACITY) + size), stride);
	memcpy(temp, tinyvec, length * stride);
	_tinyvec_field_set(temp, TINYVEC_LENGTH, length);
	_tinyvec_destroy(tinyvec);
	return temp;
}

void* _tinyvec_push(void* array, const void* value_ptr) {
	uint64_t length = tinyvec_length(array);
	uint64_t stride = tinyvec_stride(array);
	if(length >= tinyvec_capacity(array)) {
	array = _tinyvec_reserve(array, TINYVEC_RESIZE_FACTOR);
	}
	uint64_t addr = (uint64_t)array;
	addr += (length * stride);
	memcpy((void*)addr, value_ptr, stride);
	_tinyvec_field_set(array, TINYVEC_LENGTH, length + 1);
	return array;
}

void _tinyvec_pop(void* array, void* dest) {
	uint64_t length = tinyvec_length(array);
	uint64_t stride = tinyvec_stride(array);
	uint64_t addr = (uint64_t)array;
	addr += ((length - 1) * stride);
	memcpy(dest, (void*)addr, stride);
	_tinyvec_field_set(array, TINYVEC_LENGTH, length - 1);
}

void* _tinyvec_pop_at(void* array, uint64_t index, void* dest) {
	uint64_t length = tinyvec_length(array);
	uint64_t stride = tinyvec_stride(array);
	if(index >= length) {
	WAGERROR("Index outside the bounds of this array! Length:%lli, index: %lli\n", length, index);
	return array;
	}
	uint64_t addr = (uint64_t)array;
	memcpy(dest, (void*)(addr + (index * stride)), stride);
	if(index != length -1) {
	memcpy((void*)(addr +(index * stride)),(void*)(addr +((index + 1) * stride)),stride * (length - index));
	}
	_tinyvec_field_set(array, TINYVEC_LENGTH, length - 1);
	return array;
}

void* _tinyvec_insert_at(void* array, uint64_t index, void* value_ptr) {
	uint64_t length = tinyvec_length(array);
	uint64_t stride = tinyvec_stride(array);
	if(index >= length) {
	WAGERROR("Index outside the bounds of this array! Length:%lli, index: %lli\n", length, index);
	return array;
	}
	if(length >= tinyvec_capacity(array)) {
	array = _tinyvec_reserve(array, TINYVEC_RESIZE_FACTOR);
	}
	uint64_t addr = (uint64_t)array;
	if(index != length -1) {
	memcpy((void*)(addr + ((index + 1) * stride)),(void*)(addr + (index * stride)),stride * (length - index));
	}
	memcpy((void*)(addr + ((index + 1) * stride)), value_ptr, stride);
	_tinyvec_field_set(array, TINYVEC_LENGTH, length + 1);
	return array;
}

#pragma once

#include <defines.h>

typedef enum TINYVEC_FIELDS{
	TINYVEC_CAPACITY,
	TINYVEC_LENGTH,
	TINYVEC_STRIDE,
	TINYVEC_FIELD_LENGTH
} TINYVEC_FIELDS;

void* _tinyvec_create(uint64_t length, uint64_t stride);
void _tinyvec_destroy(void* tinyvec);
uint64_t _tinyvec_field_get(void* tinyvec, uint64_t field);
void _tinyvec_field_set(void* tinyvec, uint64_t field, uint64_t value);
void* _tinyvec_resize(void* tinyvec, uint64_t size);
void* _tinyvec_reserve(void* tinyvec, uint64_t size);
void* _tinyvec_push(void* tinyvec, const void* value_ptr);
void _tinyvec_pop(void* tinyvec, void* dest);
void* _tinyvec_pop_at(void* tinyvec, uint64_t index, void* dest);
void* _tinyvec_insert_at(void* tinyvec, uint64_t index, void* value_ptr);

#define TINYVEC_DEFAULT_CAPACITY 1
#define TINYVEC_RESIZE_FACTOR 2

#define tinyvec_create(type) \
	_tinyvec_create(TINYVEC_DEFAULT_CAPACITY, sizeof(type))

#define tinyvec_reserve(tinyvec, size) \
	{ \
	tinyvec = _tinyvec_reserve(tinyvec, size); \
	}

#define tinyvec_destroy(tinyvec) \
	_tinyvec_destroy(tinyvec);

#define tinyvec_push(T, tinyvec, value) \
	{ \
	T temp = value; \
	tinyvec = _tinyvec_push(tinyvec, &temp); \
	}

#define tinyvec_pop(tinyvec, value_ptr) \
	_tinyvec_pop(tinyvec, value_ptr)

#define tinyvec_insert_at(tinyvec, index, value) \
	{ \
	typeof(value) temp = value; \
	tinyvec = _tinyvec_insert_at(tinyvec, index, &temp); \
	}

#define tinyvec_pop_at(tinyvec, index, value_ptr) \
	_tinyvec_pop_at(tinyvec, index, value_ptr)

#define tinyvec_clear(tinyvec) \
	_tinyvec_field_set(tinyvec, TINYVEC_LENGTH, 0)

#define tinyvec_capacity(tinyvec) \
	_tinyvec_field_get(tinyvec, TINYVEC_CAPACITY)

#define tinyvec_length(tinyvec) \
	_tinyvec_field_get(tinyvec, TINYVEC_LENGTH)

#define tinyvec_stride(tinyvec) \
	_tinyvec_field_get(tinyvec, TINYVEC_STRIDE)

#define tinyvec_length_set(tinyvec, value) \
	_tinyvec_field_set(tinyvec, TINYVEC_LENGTH, value)

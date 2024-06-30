#pragma once

#include <defines.h>
#include <WAG/util/tinyvec.h>
// For memory efficiency we wil have limited event message size
#define EVENT_MSG_SIZE 128
typedef union _EventMsg {
	uint64_t ulong_msg[EVENT_MSG_SIZE / sizeof(uint64_t)]; 
	uint32_t uint_msg[EVENT_MSG_SIZE / sizeof(uint32_t)];
	uint16_t ushort_msg[EVENT_MSG_SIZE / sizeof(uint16_t)];
	uint8_t  byte_msg[EVENT_MSG_SIZE / sizeof(uint8_t)];
} EventMsg;

typedef enum _EventType {
	EVENT_NONE = 0, // Should not happen
	EVENT_SHUTDOWN = 1,
	EVENT_WINDOW_CLOSE = 2,
	EVENT_WINDOW_RESIZE = 3,
	EVENT_WINDOW_FOCUS = 4,
	EVENT_WINDOW_LOSE_FOCUS = 5,
	EVENT_KEY_PRESSED = 6, // You need to use these 6
	EVENT_KEY_RELEASED = 7,
	EVENT_MOUSE_BUTTON_PRESSED = 8,
	EVENT_MOUSE_BUTTON_RELEASED = 9,
	EVENT_MOUSE_MOVED = 10,
	EVENT_MOUSE_SCROLLED = 11,

	EVENT_MAX // For array calc
} EventType;

typedef struct _Event {
	EventMsg msg;
} Event;

typedef bool (*EventHandler)(Event* event);



void EventSystemInit(void* block, size_t* size);
void EventRegisterHandler(EventType type, EventHandler handler);
bool EventDispatch(Event* event);
void EventSystemShutdown();
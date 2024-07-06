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
	/**
	 * @brief Triggered when the application should shutdown or encounter an unrecoverable error.
	 * @param ErrorCode the error code located at byte_msg[0]
	 * @param ErrorMessage the error message located from byte_msg[1] up to byte_msg[EVENT_MSG_SIZE - 1]
	 */
	EVENT_SHUTDOWN = 1,
	/**
	 * @brief Triggered when the window closes.
	 * @brief Generally unused by the engine but application can subscribe to it
	 */
	EVENT_WINDOW_CLOSE = 2,
	/**
	 * @brief Triggered when the window resizes.
	 * @brief Generally used by the renderer
	 * @param width the new width located at uint_msg[0]
	 * @param height the new height located at uint_msg[1]
	 */
	EVENT_WINDOW_RESIZE = 3,
	/**
	 * @brief Triggered when the window gets focus
	 * @brief Generally unused by the engine but application can subscribe to it
	 */
	EVENT_WINDOW_FOCUS = 4,
	/**
	 * @brief Triggered when the window loses focus
	 * @brief Generally unused by the engine but application can subscribe to it
	 */
	EVENT_WINDOW_LOSE_FOCUS = 5,
	/**
	 * @brief Triggered when a key is pressed
	 * @details this is for both key and mouse button cause we store it in the same array
	 * @param key the key that was pressed located at uint_msg[0]
	 * @param pressed true if the key was pressed located at byte_msg[4]
	 */
	EVENT_KEY_AND_MOUSE_BUTTON = 6, 

	/**
	 * @brief Triggered when the mouse is moved
	 * @param x the amount moved on the x axis located at uint_msg[0]
	 * @param y the amount moved on the y axis located at uint_msg[4]
	 */
	EVENT_MOUSE_MOVED = 7,

	/**
	 * @brief Triggered when the mouse middle button is scrolled
	 * @param x the amount scrolled on the x axis located at uint_msg[0]
	 */
	EVENT_MOUSE_SCROLLED = 8,

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
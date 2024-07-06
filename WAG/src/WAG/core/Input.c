#include <WAG/core/Input.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/Event.h>
#include <WAG/core/Logger.h>
#include <string.h>
#include <assert.h>

typedef struct _input_internals {
	// TODO: Vec2
	int mouseX;
	int mouseY;
	int oldMouseX;
	int oldMouseY;
	bool pressed[256];
	bool old[256];
	// TODO: ALSO STORE MOUSE BUTTONS
} input_internals;

static input_internals* input = NULL; 

bool InputKeyHandler(Event* e) {
	if(!input) {
		WAGDEBUG("Tried to call InputKeyHandler with uninitialized Input");
		return true;
	}
	int key = e->msg.byte_msg[0];
	bool pressed = e->msg.byte_msg[1];
	if(key < 0 || key >= KEYS_MAX_KEYS) return false; // Literally impossible BUT JUST IN CASE
	input->pressed[key] = pressed;
	return true;
}

bool InputMouseHandler(Event* e) {
	if(!input) {
		WAGDEBUG("Tried to call InputMouseHandler with uninitialized Input");
		return true;
	}
	input->mouseX = e->msg.int_msg[0];
	input->mouseY = e->msg.int_msg[1];
	return true;
}

bool InputInit(void* block, size_t* size){
  if(block == NULL) {
    *size = sizeof(input_internals);
    return true;
  }
	assert(input == NULL && "Attempted to initialize Input twice");
	input = (input_internals*)block;
	memset(input, 0, sizeof(input_internals));
	EventRegisterHandler(EVENT_KEY_AND_MOUSE_BUTTON, InputKeyHandler);
	EventRegisterHandler(EVENT_MOUSE_MOVED, InputMouseHandler);
	return true;
}

void InputUpdate() {
	memmove(input->old, input->pressed, sizeof(bool) * KEYS_MAX_KEYS);
	input->oldMouseX = input->mouseX;
	input->oldMouseY = input->mouseY;
}

void InputShutdown() {
	input = NULL;
}

bool GetKey(keys button) {
	return input->pressed[button];
}

bool GetKeyDown(keys button) {
	return !input->old[button] && input->pressed[button]; 
}

bool GetKeyUp(keys button) {
	return input->old[button] && !input->pressed[button];
}

bool GetButton(buttons button) {
	return input->pressed[button];
}
bool GetButtonDown(buttons button) {
	return !input->old[button] && input->pressed[button];
}
bool GetButtonUp(buttons button) {
	// in reverse
	return input->old[button] && !input->pressed[button];
}


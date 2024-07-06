#include <WAG/core/Input.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/Event.h>
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

void InputKeyHandler(Event* e) {
	int key = e->msg.byte_msg[0];
	bool pressed = e->msg.byte_msg[1];
	if(key < 0 || key >= KEYS_MAX_KEYS) return;
	input->pressed[key] = pressed;
}

void InputMouseHandler(int x, int y) {
	input->mouseX = x;
	input->mouseY = y;
}

void InputInit(void* block, size_t* size){
  if(block == NULL) {
    *size = sizeof(input_internals);
    return;
  }
	assert(input == NULL && "Attempted to initialize Input twice");
	input = (input_internals*)block;
	memset(input, 0, sizeof(input_internals));
}

void InputUpdate() {
	memmove(input->old, input->pressed, sizeof(bool) * KEYS_MAX_KEYS);
	input->oldMouseX = input->mouseX;
	input->oldMouseY = input->mouseY;
}

void InputShutdown()
{
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


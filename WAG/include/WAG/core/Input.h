#pragma once

#include <defines.h>

// Basically we will store 2 arrays, currently pressed and it's old copy
typedef enum _keycode {
	KEYCODE_0 = '0',
    KEYCODE_1,
    KEYCODE_2,
    KEYCODE_3,
    KEYCODE_4,
    KEYCODE_5,
    KEYCODE_6,
    KEYCODE_7,
    KEYCODE_8,
    KEYCODE_9,

    KEYCODE_A = 'A',
    KEYCODE_B,
    KEYCODE_C,
    KEYCODE_D,
    KEYCODE_E,
    KEYCODE_F,
    KEYCODE_G,
    KEYCODE_H,
    KEYCODE_I,
    KEYCODE_J,
    KEYCODE_K,
    KEYCODE_L,
    KEYCODE_M,
    KEYCODE_N,
    KEYCODE_O,
    KEYCODE_P,
    KEYCODE_Q,
    KEYCODE_R,
    KEYCODE_S,
    KEYCODE_T,
    KEYCODE_U,
    KEYCODE_V,
    KEYCODE_W,
    KEYCODE_X,
    KEYCODE_Y,
    KEYCODE_Z,

		KEYCODE_MAX
} input_keycode;

void InputInit(void* block, size_t* size);
void InputUpdate();
void InputShutdown();

bool GetButton(input_keycode button);
bool GetButtonDown(input_keycode button);
bool GetButtonUp(input_keycode button);
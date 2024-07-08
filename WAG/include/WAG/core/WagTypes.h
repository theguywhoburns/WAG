#pragma once

#include <defines.h>

typedef struct WagException {
	int line;
	char* message;
	char* file;
} WagException;
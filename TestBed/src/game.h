#pragma once

#include <WAG/core/Application.h>

struct ApplicationSpecificData {
	int a;
};

bool OnCreate(Application* app);
bool OnUpdate(Application* app);
bool OnFixedUpdate(Application* app);
bool OnDestroy(Application* app);
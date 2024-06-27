#pragma once

#include <defines.h>
#include <WAG/core/Engine.h>

typedef struct ApplicationSpecificData ApplicationSpecificData;
typedef struct ApplicationCreationInfo ApplicationCreationInfo;

typedef struct Application {
	bool (*OnCreate)(struct Application* app);
	bool (*OnUpdate)(struct Application* app);
	bool (*OnFixedUpdate)(struct Application* app);
	bool (*OnDestroy)(struct Application* app);
	size_t AppSpecificDataSize;
	ApplicationSpecificData* data;
} Application;

struct ApplicationCreationInfo {
	int windowWidth, windowHeight;
	char* AppName;
	size_t AppSpecificDataSize;
	ApplicationSpecificData* data;
	bool (*OnCreate)(struct Application* app);
	bool (*OnUpdate)(struct Application* app);
	bool (*OnFixedUpdate)(struct Application* app);
	bool (*OnDestroy)(struct Application* app);
};
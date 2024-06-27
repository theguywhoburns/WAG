#pragma once

#include <defines.h>

struct Application;
typedef struct EngineInternalData EngineInternalData;

typedef struct Engine {
	EngineInternalData* internal;
	struct Application* app_instance;
} Engine;

WAG_API Engine* GetEngineInstance(); //Wtf?
WAG_API Engine* InitializeEngine(struct ApplicationCreationInfo* appInfo, int argc, char** argv[]);

WAG_API bool RunEngine(Engine* engine);
WAG_API void DestroyEngine(Engine* engine);
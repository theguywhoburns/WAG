#pragma once

#include <defines.h>

struct Application;
typedef struct EngineInternalData EngineInternalData;
// !!!
// !!! TODO: GET RID OF ALL ASSERTIONS AND REPLACE THEM TO RETURN FALSE
// !!!
typedef struct Engine {
	EngineInternalData* internal;
	struct Application* app_instance;
	bool is_running;
} Engine;

WAG_API Engine* GetEngineInstance(); 
WAG_API Engine* InitializeEngine(struct ApplicationCreationInfo* appInfo, int argc, char** argv[]);

WAG_API bool RunEngine(Engine* engine);
WAG_API void DestroyEngine(Engine* engine);
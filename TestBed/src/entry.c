#include <WAG/entry.h>
#include <WAG/core/MemoryManagement.h>
#include <stdlib.h>
#include "game.h"

ApplicationCreationInfo GetAppInfo() {
	// TODO: Get rid of malloc
	ApplicationSpecificData* data = walloc(sizeof(ApplicationSpecificData), MEMORY_APPLICATION); // This fixed the issue with crash on attempt to de-allocate
	ApplicationCreationInfo appInfo = {
		.data = data,
		.AppSpecificDataSize = 
		sizeof(ApplicationSpecificData),
		.OnCreate = OnCreate,
		.OnUpdate = OnUpdate,
		.OnFixedUpdate = OnFixedUpdate,
		.OnDestroy = OnDestroy
	};
	return appInfo;
}
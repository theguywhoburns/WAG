#include  <WAG/entry.h>
#include <stdlib.h>
#include "game.h"

ApplicationCreationInfo GetAppInfo() {
	// TODO: Get rid of malloc
	ApplicationSpecificData* data = malloc(sizeof(ApplicationSpecificData));
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
#include <assert.h>
#include <WAG/core/Engine.h>
#include <WAG/core/Application.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/FlatAllocator.h>

// TODO:
struct EngineInternalData {
	FlatAllocator* engine_internal_memory_block;
	
	// Logger handle

	// Platform handle
	
	// Memory manager handle

	// Renderer handle

	// Input system handle
};

static Engine* engine = NULL;

WAG_API Engine* GetEngineInstance() {
	return engine;
}

WAG_API Engine* InitializeEngine(struct ApplicationCreationInfo* appInfo, int argc, char** argv[]) {
	assert(engine == NULL);

	engine = (Engine*)walloc(sizeof(Engine), MEMORY_ENGINE);
	engine->internal = (EngineInternalData*)walloc(sizeof(EngineInternalData), MEMORY_ENGINE);
	// 60 megabytes as starting memory is ok
	engine->internal->engine_internal_memory_block = FlatAllocatorCreate(NULL, 1024 * 1024 * 60, true);
	
	return engine;
}

WAG_API bool RunEngine(engine) {

	return true;
}

WAG_API void DestroyEngine(engine) {

}

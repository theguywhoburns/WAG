#include <assert.h>
#include <WAG/core/Engine.h>
#include <WAG/core/Application.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/FlatAllocator.h>
#include <WAG/core/Logger.h>
#include <WAG/core/Input.h>
#include <WAG/core/Event.h>
#include <WAG/platform/Platform.h>

// TODO:
struct EngineInternalData {
	FlatAllocator* engine_internal_memory_block;
	
	// Logger handle
	uint64_t logger_memory_size;
	void*    logger_memory_block;
	// Platform handle
	uint64_t platform_memory_size;
	void*    platform_memory_block;
	// Memory manager handle
	uint64_t memory_manager_memory_size;
	void*    memory_manager_memory_block;
	// Event system handle
	uint64_t event_memory_size;
	void*    event_memory_block;
	// Input system handle
	uint64_t input_memory_size;
	void*    input_memory_block;
	// Renderer handle
	uint64_t renderer_memory_size;
	void*    renderer_memory_block;
};

static Engine* engine = NULL;

Engine* GetEngineInstance() {
	return engine;
}

Engine* InitializeEngine(struct ApplicationCreationInfo* appInfo, int argc, char** argv[]) {
	assert(engine == NULL);
	assert(appInfo->OnCreate != NULL && "OnCreate" != NULL);
	assert(appInfo->OnUpdate != NULL && "OnUpdate" != NULL);
	assert(appInfo->OnFixedUpdate != NULL && "OnFixedUpdate" != NULL);
	assert(appInfo->OnDestroy != NULL && "OnDestroy" != NULL);
	
	engine = (Engine*)walloc(sizeof(Engine), MEMORY_ENGINE);
	engine->internal = (EngineInternalData*)walloc(sizeof(EngineInternalData), MEMORY_ENGINE);
	// 60 megabytes as starting memory is ok
	#define prealloc_size 1024 * 1024 * 60
	// We pre-allocate the memory for all subsystems here
	engine->internal->engine_internal_memory_block = FlatAllocatorCreate(NULL, prealloc_size, true);
	// Memory subsystem
	wmem_init(NULL, &engine->internal->memory_manager_memory_size);
	engine->internal->memory_manager_memory_block = walloc(engine->internal->memory_manager_memory_size, MEMORY_NO_AUTO_DEALLOC);
	wmem_init(engine->internal->memory_manager_memory_block, &engine->internal->memory_manager_memory_size);
	__mem_add_value(MEMORY_ENGINE, engine, sizeof(Engine));
	__mem_add_value(MEMORY_ENGINE, engine->internal, sizeof(EngineInternalData));
	__mem_add_value(MEMORY_PREALLOCATOR, engine->internal->engine_internal_memory_block, prealloc_size);

	// Platform subsystem
	PlatformInitialize(appInfo, NULL, &engine->internal->platform_memory_size);
	engine->internal->platform_memory_block = FlatAllocatorAlloc(engine->internal->engine_internal_memory_block, engine->internal->platform_memory_size);
	PlatformInitialize(appInfo, engine->internal->platform_memory_block, &engine->internal->logger_memory_size);

	// Logger subsystem
	LoggerInitialize(NULL, &engine->internal->logger_memory_size);
	engine->internal->logger_memory_block = FlatAllocatorAlloc(engine->internal->engine_internal_memory_block, engine->internal->logger_memory_size);
	LoggerInitialize(engine->internal->logger_memory_block, &engine->internal->logger_memory_size);

	// Event subsystem
	EventSystemInit(NULL, &engine->internal->event_memory_size);
	engine->internal->event_memory_block = FlatAllocatorAlloc(engine->internal->engine_internal_memory_block, engine->internal->event_memory_size);
	EventSystemInit(engine->internal->event_memory_block, &engine->internal->event_memory_size);

	// Input subsystem
	InputInit(NULL, &engine->internal->input_memory_size);
	engine->internal->input_memory_block = FlatAllocatorAlloc(engine->internal->engine_internal_memory_block, engine->internal->input_memory_size);
	InputInit(engine->internal->input_memory_block, &engine->internal->input_memory_size);

	// Application 
	Application* app = walloc(sizeof(Application), MEMORY_APPLICATION);
	app->data = appInfo->data;
	app->OnCreate = appInfo->OnCreate;
	app->OnUpdate = appInfo->OnUpdate;
	app->OnFixedUpdate = appInfo->OnFixedUpdate;
	app->OnDestroy = appInfo->OnDestroy;
	engine->app_instance = app;

	return engine;
}

bool RunEngine(Engine* engine) {
	// Just a while loop that updates all the subsystems
	engine->is_running = true;
	engine->app_instance->OnCreate(engine->app_instance);
	size_t i = 0;
	while (engine->is_running) {
		if(!PlatformUpdate()) {
			WAGERROR("PlatformUpdate failed");
			engine->is_running = false;
		}
		if(!engine->app_instance->OnUpdate(engine->app_instance)) {
			WAGERROR("OnUpdate failed");
			engine->is_running = false;
		}
		if(i > 100000) {
			engine->is_running = false;
		}
		i++;
	}
	engine->app_instance->OnDestroy(engine->app_instance);
	return true;
}

void DestroyEngine(Engine* engine) {
	// Shutdown everything in the reverse order of initialization
	// Then free the memory
	InputShutdown();
	LoggerShutdown();
	PlatformShutdown();
	EventSystemShutdown();
	#if _DEBUG
		__print_allocation_map();
	#endif
	wmem_shutdown();
	wfree(engine->internal, sizeof(EngineInternalData), MEMORY_ENGINE);
	wfree(engine->app_instance->data, engine->app_instance->AppSpecificDataSize, MEMORY_APPLICATION);
	wfree(engine->app_instance, sizeof(Application), MEMORY_APPLICATION);
	wfree(engine, sizeof(Engine), MEMORY_ENGINE);
}

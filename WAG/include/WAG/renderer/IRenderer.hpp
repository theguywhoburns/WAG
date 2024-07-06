#pragma once

#include <defines.h>
#include <WAG/util/lib.h>

typedef struct RendererInternals RendererInternals;

typedef struct IRendererInterface {
	DynamicLibrary handle;
	RendererInternals* internals;
	bool (*Initialize)(struct IRenderer* renderer);
	bool (*BeginFrame)(struct IRenderer* renderer);
	bool (*Render)(struct IRenderer* renderer);
	bool (*EndFrame)(struct IRenderer* renderer);
	bool (*Present)(struct IRenderer* renderer);
	bool (*Release)(struct IRenderer* renderer);
} IRendererInterface;

// Path should be supplied from the config file, will return false on fail
bool  LoadRenderer(const char* path, IRendererInterface* renderer);
void UnloadRenderer(IRendererInterface* renderer);
#pragma once

#include <pp_util.h>
#include <WAG.h>

#ifdef BINDGEN
#define RENDERER_API_FUNC(type, name, ...) PP_TFUNC(type, name, __VA_ARGS__); type _##name(__VA_ARGS__);
#else
#define RENDERER_API_FUNC(type, name, ...) PP_TFUNC(type, name, __VA_ARGS__)
#endif

typedef struct RendererInterface RendererInterface;

RENDERER_API_FUNC(void, PFNRendererInitialize,  WAG* engine, RendererInterface* renderer, void* window_handle);
RENDERER_API_FUNC(void, PFNRendererUpdate,      WAG* engine, RendererInterface* renderer);
RENDERER_API_FUNC(void, PFNRendererShutdown,    WAG* engine, RendererInterface* renderer);
RENDERER_API_FUNC(RendererInterface, PFNRendererGetInterface, size_t* data_size);

struct RendererInterface {
    PFNRendererInitialize Initialize;
    PFNRendererUpdate Update;
    PFNRendererShutdown Shutdown;
    void* data;
};
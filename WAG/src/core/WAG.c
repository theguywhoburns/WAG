#include <WAG.h>
#include <interface/application.h>
#include <core/logger.h>

#include <util/str.h>
#include <util/heap_alloc.h>
PP_TSTRUCT(WAGInternal);
struct WAGInternal {

#define DefineSubsystem(name) void* name##_ptr; size_t name##_size;
    DefineSubsystem(memory_subsystem);
    DefineSubsystem(window_subsystem);
    DefineSubsystem(input_subsystem);
    DefineSubsystem(render_subsystem);
    DefineSubsystem(logger_subsystem);
};

bool StartWAG(WAG* wag, appinfo* info) {
#define APP_INFO_PFN_CHECK(pfnname) if(!info->pfnname) { WAG_FATAL(PP_STRINGIFY(pfnname) " is not set, but it is a required function"); return false; }
    APP_INFO_PFN_CHECK(OnCreate);
    APP_INFO_PFN_CHECK(OnUpdate);
    APP_INFO_PFN_CHECK(OnFixedUpdate);
    APP_INFO_PFN_CHECK(OnDestroy);
#undef APP_INFO_PFN_CHECK
    if(info->dwinw  == 0) { WAG_ERROR("Default window width must be greater than 0"); return false; }
    if(info->dwinh  == 0) { WAG_ERROR("Default window height must be greater than 0"); return false; }
    if(info->datalen== 0) { WAG_WARN("Application info supplied with 0 data length, this may cause undefined behaviour"); }
    if(str_len(info->name) == 0) WAG_WARN("Application info supplied with empty name, setting it to \"WAG\"");
    // else is not required here because we will allocate it after initializing the subsystems
    if(!info->fixed_timestep) wag->delta_time = 1000.0f / 20.0f; // 20 ticks per 1000 milliseconds
    else wag->delta_time = info->fixed_timestep; // Highly unrecommended to modify this value

    *wag = (WAG){0};



    return true; // Will only return once the engine finishes working
}
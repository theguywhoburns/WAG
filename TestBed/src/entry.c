#include <entry.h>
#include <game.h>

void GetAppInfo(appinfo* info) {
    *info = (appinfo) {
        .name = "WAG: Testbed",
        .dwinw = 800,
        .dwinh = 600,
        .data = 0,
        .datalen = sizeof(TestBed),
        .fixed_timestep = 0.0,
        .OnCreate = (PFNOnCreate)OnCreate,
        .OnUpdate = (PFNOnUpdate)OnUpdate,
        .OnFixedUpdate = (PFNOnFixedUpdate)OnFixedUpdate,
        .OnDestroy = (PFNOnDestroy)OnDestroy
    };
}
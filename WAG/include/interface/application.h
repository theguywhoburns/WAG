#pragma once

#include <pp_util.h>
#include <WAG.h>

PP_TSTRUCT(appinfo);
PP_TFUNC(bool, PFNOnCreate,     WAG* engine, uintptr_t app_data);
PP_TFUNC(bool, PFNOnUpdate,     WAG* engine, uintptr_t app_data);
PP_TFUNC(bool, PFNOnFixedUpdate,WAG* engine, uintptr_t app_data);
PP_TFUNC(bool, PFNOnDestroy,    WAG* engine, uintptr_t app_data);

///@brief Application information, used for initialization
///@param name Name of the application
///@param def_window_width Default window width
///@param def_window_height Default window height
///@param data Application specific data
///@param datalen Size of the data
///@param fixed_timestep NULLABLE, Fixed timestep, if set to 0.0 the engine will make it into 20 times a second
///@param OnCreate NONNULL, Called when the application is created
///@param OnUpdate NONNULL, Called every frame
///@param OnFixedUpdate NONNULL, Called every fixed timestep
///@param OnDestroy NONNULL, Called when the application is destroyed  
struct appinfo {
    ///@brief Name of the application, can be changed later using the WAG internal functions
    char name[256];
    ///@brief Default window width
    size_t dwinw;
    ///@brief Default window height
    size_t dwinh;
    ///@brief Application specific data
    uintptr_t data;
    ///@brief Size of the data
    size_t datalen;
    ///@brief Fixed timestep, if set to 0.0 the engine will make it into 20 times a second
    ///@warning NULLABLE
    double fixed_timestep; 
    ///@brief Called when the application is created
    ///@param engine Pointer to the WAG engine
    ///@param app_data Application specific data
    ///@warning NONNULL
    PFNOnCreate OnCreate;
    ///@brief Called every frame
    ///@param engine Pointer to the WAG engine
    ///@param app_data Application specific data
    ///@warning NONNULL
    PFNOnUpdate OnUpdate;
    ///@brief Called every fixed timestep, can be configured on the startup
    ///@param engine Pointer to the WAG engine
    ///@param app_data Application specific data
    ///@warning NONNULL
    PFNOnFixedUpdate OnFixedUpdate;
    ///@brief Called when the application is destroyed
    ///@param engine Pointer to the WAG engine
    ///@param app_data Application specific data
    ///@warning NONNULL
    PFNOnDestroy OnDestroy;
};
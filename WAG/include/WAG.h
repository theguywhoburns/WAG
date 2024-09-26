#pragma once

#include <pp_util.h>

#define WAG_VERSION PP_VERSION_COMPOSE(WAG_MAJOR, WAG_MINOR, WAG_PATCH)
#define WAG_VERSION_STR PP_STRINGIFY(WAG_MAJOR.WAG_MINOR.WAG_PATCH);

PP_TSTRUCT(WAG);
struct WAG {
    double delta_time;
    void* internal_data;
} packed;


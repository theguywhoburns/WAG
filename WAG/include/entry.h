#pragma once

#include <pp_util.h>
#include <WAG.h>
#include <interface/application.h>
//HACK: need to get rid of this
extern void GetAppInfo(appinfo* info);

//TODO: idk but we need to throw this function somewhere else
bool StartWAG(WAG* wag, appinfo* info);

int main(int argc, char* argv[]) {
    appinfo info;
    GetAppInfo(&info);
    WAG engine;
    if(!StartWAG(&engine, &info)) return -1;
    return 0;
}

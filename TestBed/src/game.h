#pragma once

#include <WAG.h>

typedef struct TestBed {
    void* temp;
} TestBed;

bool OnCreate(WAG* engine, TestBed* testbed);
bool OnUpdate(WAG* engine, TestBed* testbed);
bool OnFixedUpdate(WAG* engine, TestBed* testbed);
bool OnDestroy(WAG* engine, TestBed* testbed);
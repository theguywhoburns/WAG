#include <pp_util.h>

#if PLATFORM_WINDOWS

#include <windows.h>

bool PlatformInitialize(void* block, size_t* size) {

}

void PlatformShutdown() {

}

bool PlatformUpdate() {

}

void*PlatformAllocate(size_t size) {
    return VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

void PlatformFree(void* ptr) {
    VirtualFree(ptr, 0, MEM_RELEASE);
}

#endif// PLATFORM_WINDOWS
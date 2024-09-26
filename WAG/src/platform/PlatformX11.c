#include <platform/platform.h>

#if PLATFORM_LINUX || PLATFORM_UNIX 
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/mman.h>
#include <memory.h>
#include <unistd.h>
#include <stdlib.h>

bool PlatformInitialize(void* block, size_t* size) {

}

void PlatformShutdown() {

}

bool PlatformUpdate() {

}

void*PlatformAllocate(size_t size) {
    return malloc(size);
}

void PlatformFree(void* ptr) {
    free(ptr);
}

#endif // PLATFORM_LINUX || PLATFORM_UNIX
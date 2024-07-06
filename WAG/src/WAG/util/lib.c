#include <WAG/util/lib.h>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#elif PLATFORM_LINUX
#include <dlfcn.h>
#endif

DynamicLibrary DynamicLibraryCreate(const char* path) {
#ifdef PLATFORM_WINDOWS
	return (DynamicLibrary){LoadLibraryA(path)};
#elif PLATFORM_LINUX
	return (DynamicLibrary){dlopen(path, RTLD_NOW)};
#endif
}

void DynamicLibraryDestroy(DynamicLibrary* library) {
#ifdef PLATFORM_WINDOWS
	FreeLibrary((HMODULE)library->handle);
#elif PLATFORM_LINUX
	dlclose(library->handle);
#endif
}

void* __DynamicLibraryGetFunction(DynamicLibrary* lib, const char* name) {
#ifdef PLATFORM_WINDOWS
	return (void*)GetProcAddress((HMODULE)lib->handle, name);
#elif PLATFORM_LINUX
	return (void*)dlsym(handle, name);
#endif
}
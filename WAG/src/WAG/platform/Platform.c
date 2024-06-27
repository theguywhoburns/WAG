#include <WAG/platform/Platform.h>
#include <WAG/core/MemoryManagement.h>
#ifdef PLATFORM_WINDOWS

#include <Windows.h>

struct PlatformInternalData {
	HWND window_handle;
	ATOM class_handle;
	HINSTANCE instance_handle;
};

static PlatformInternalData* platform = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//continue
bool PlatformInitialize(ApplicationCreationInfo* info, void* block, uint64_t* size) {
	assert(platform == NULL);
	if(block == NULL) {
		*size = sizeof(PlatformInternalData);
		return true;
	}

	platform = (PlatformInternalData*)block;
	platform->window_handle = NULL;
	platform->class_handle = NULL;

	WNDCLASSEXW _class = {sizeof(WNDCLASSEXW)};
	_class.style = CS_HREDRAW | CS_VREDRAW;
	_class.hInstance = GetModuleHandle(NULL);
	_class.lpfnWndProc = WndProc;
	_class.lpszClassName = L"WAG";
	_class.hIcon = NULL;
	_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	_class.lpszMenuName = NULL;
	_class.cbClsExtra = 0;
	_class.cbWndExtra = 0;
	_class.hIconSm = NULL;
	platform->class_handle = RegisterClassExW(&_class);
	if(!platform->class_handle) {
		// TODO: Log error
		return false;
	}

	platform->instance_handle = _class.hInstance;

	int size = MultiByteToWideChar(CP_UTF8, 0, info->AppName, -1, NULL, 0);
	wchar_t* name = (wchar_t*)walloc(size, MEMORY_ENGINE);
    size = MultiByteToWideChar(CP_UTF8, 0, info->AppName, -1, name, size);
    if(!size)  {
    // TODO: Log error
		return false;
    }

	platform->window_handle = CreateWindowExW(0, _class.lpszClassName, name , WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, info->windowWidth, info->windowHeight, NULL, NULL, _class.hInstance, NULL);
	if(!platform->window_handle) {
		// TODO: Log error
		return false;
	}

	return true;
}

bool PlatformUpdate() {
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE) != 0) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return true;
}

void PlatformShutdown() {
	if(platform->window_handle) {
		DestroyWindow(platform->window_handle);
		platform->window_handle = NULL;
	}

	if(platform->class_handle) {
		UnregisterClassW((LPCWSTR)platform->class_handle, platform->instance_handle);
		platform->class_handle = NULL;
	}
	
	platform = NULL;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProcW(hWnd, message, wParam, lParam);
}

void* PlatformAllocate(size_t size, bool align) {
	void* ret = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	return ret;
}

void  PlatformFree(void* block) {
	VirtualFree(block, 0, MEM_RELEASE);
}

#endif
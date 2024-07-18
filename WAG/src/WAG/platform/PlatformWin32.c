#include <WAG/platform/Platform.h>
#include <WAG/core/MemoryManagement.h>
#include <WAG/core/Event.h>
#include <WAG/core/Logger.h>
#include <WAG/core/Input.h>
#ifdef PLATFORM_WINDOWS
#include <assert.h>
#include <windows.h>
#include <windowsx.h>  // param input extraction

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
	platform->window_handle = 0;
	platform->class_handle = 0;

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

	int _size = MultiByteToWideChar(CP_UTF8, 0, info->AppName, -1, NULL, 0);
	wchar_t* name = (wchar_t*)walloc(_size, MEMORY_ENGINE);
    _size = MultiByteToWideChar(CP_UTF8, 0, info->AppName, -1, name, _size);
    if(!_size)  {
    // TODO: Log error
		WAGERROR("Failed to convert string: %d", GetLastError());
		return false;
    }

	platform->window_handle = CreateWindowExW(0, _class.lpszClassName, name , WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, info->windowWidth, info->windowHeight, NULL, NULL, _class.hInstance, NULL);
	if(!platform->window_handle) {
		// TODO: Log error
		WAGERROR("Failed to create window: %d", GetLastError());
		return false;
	}
	ShowWindow(platform->window_handle, SW_SHOW);
	UpdateWindow(platform->window_handle);
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
		platform->class_handle = (ATOM)NULL;
	}
	
	platform = NULL;
}

void* PlatformAllocate(size_t size, bool align) {
	void* ret = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	return ret;
}

void  PlatformFree(void* block) {
	VirtualFree(block, 0, MEM_RELEASE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
		Event e = {0};
		strcpy(e.msg.ubyte_msg + 1, "Window close requested"); 
		EventDispatch(EVENT_SHUTDOWN, &e);// Empty event cause we close the window
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
    // Notify the OS that erasing will be handled by the application to prevent flicker.
    return 1;
		break;
	case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
  case WM_KEYUP:
  case WM_SYSKEYUP:
	  bool pressed = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
	  uint16_t key = (uint16_t)wParam;

	  // Check for extended scan code.
	  bool is_extended = (HIWORD(lParam) & KF_EXTENDED) == KF_EXTENDED;

	  // Keypress only determines if _any_ alt/ctrl/shift key is pressed. Determine which one if so.
	  if (wParam == VK_MENU) {
	    key = is_extended ? KEY_RALT : KEY_LALT;
	  } else if (wParam == VK_SHIFT) {
	    // Annoyingly, KF_EXTENDED is not set for shift keys.
	    uint32_t left_shift = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
	    uint32_t scancode = ((lParam & (0xFF << 16)) >> 16);
	    key = scancode == left_shift ? KEY_LSHIFT : KEY_RSHIFT;
	  } else if (wParam == VK_CONTROL) {
	    key = is_extended ? KEY_RCONTROL : KEY_LCONTROL;
	  }

	  // HACK: This is gross windows keybind crap.
	  if (key == VK_OEM_1) {
	    key = KEY_SEMICOLON;
	  }
	  
		// NOTE: This is a hack. if named e, it breaks the compiler...	idk why lol
		Event _e = {0};
		_e.msg.uint_msg[0] = key;
		_e.msg.byte_msg[2] = pressed;
		EventDispatch(EVENT_KEY_AND_MOUSE_BUTTON, &_e);
		// Return 0 to prevent default window behaviour for some keypresses, such as alt.
	  return 0;
	case WM_MOUSEMOVE: {
    // Mouse move
    int x_position = GET_X_LPARAM(lParam);
    int y_position = GET_Y_LPARAM(lParam);
    // Pass over to the input subsystem.

		Event e = {0};
		e.msg.int_msg[0] = x_position;	
		e.msg.int_msg[1] = y_position;
		EventDispatch(EVENT_MOUSE_MOVED, &e);
  } break;
  case WM_MOUSEWHEEL: {
  	int z_delta = GET_WHEEL_DELTA_WPARAM(wParam);
 	 	if (z_delta != 0) {
 	  	// Flatten the input to an OS-independent (-1, 1)
	    z_delta = (z_delta < 0) ? -1 : 1;

	    Event e = {0};
	    e.msg.int_msg[0] = z_delta;
	    EventDispatch(EVENT_MOUSE_SCROLLED, &e);
 	 	}
 	} break;
	case WM_LBUTTONDOWN:
  case WM_MBUTTONDOWN:
  case WM_RBUTTONDOWN:
  case WM_LBUTTONUP:
  case WM_MBUTTONUP:
  case WM_RBUTTONUP: {
    bool pressed = message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN;
    buttons mouse_button = BUTTON_MAX_BUTTONS;
    switch (message) {
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
        mouse_button = BUTTON_LEFT;
        break;
      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP:
        mouse_button = BUTTON_MIDDLE;
        break;
      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
        mouse_button = BUTTON_RIGHT;
      break;
    }
    // Pass over to the input subsystem.
    if (mouse_button != BUTTON_MAX_BUTTONS) {
      
			Event e = {0};
			e.msg.byte_msg[0] = mouse_button;
			e.msg.byte_msg[1] = pressed;
			EventDispatch(EVENT_KEY_AND_MOUSE_BUTTON, &e);
    }
	} break;
	default:
		break;
	}

	return DefWindowProcW(hWnd, message, wParam, lParam);
}
#endif
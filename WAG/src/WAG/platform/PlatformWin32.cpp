#include <WAG/platform/Platform.hpp>

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void* Platform::RendererSpecificData = nullptr;

class PlatformSpecificData {
public:	
	ATOM wnd_class = NULL;
	HWND main_wnd  = NULL;
};

bool Platform::initialized = false;
PlatformSpecificData* Platform::data = nullptr;

void Platform::Initialize(std::wstring title, int width, int height) {
	if(initialized) return;
	initialized = true;
	data = new PlatformSpecificData();

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = L"WAG";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	data->wnd_class = RegisterClassExW(&wcex);
	if (!data->wnd_class) {
		throw new std::exception("Failed to register class");
	}

	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	data->main_wnd = CreateWindowW(L"WAG", title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, wcex.hInstance, nullptr);
	if (!data->main_wnd) {
		throw new std::exception("Failed to create window");
	}

	ShowWindow(data->main_wnd, SW_SHOWNORMAL);
	UpdateWindow(data->main_wnd);
}

void Platform::Update() {
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Platform::Shutdown() {
	initialized = false;
	delete data;
}

bool Platform::IsInitiallized() {
	return initialized;
}

void Platform::Show(bool show) {
	if(!initialized) return;
	ShowWindow(data->main_wnd, show ? SW_SHOWNORMAL : SW_HIDE);
}

void Platform::SetTitle(std::wstring title) {
	if(!initialized) return;
	SetWindowTextW(data->main_wnd, title.c_str());
}

std::wstring Platform::GetTitle() {
	if(!initialized) return L"";
	wchar_t buf[256];
	GetWindowTextW(data->main_wnd, buf, 256);
	return buf;
}

void Platform::SetSize(int width, int height) {
	if(!initialized) return;
	SetWindowPos(data->main_wnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

void Platform::SetPosition(int x, int y) {
	if(!initialized) return;
	SetWindowPos(data->main_wnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

glm::vec2 Platform::GetSize() {
	if(!initialized) return glm::vec2(0);
	RECT rect;
	GetClientRect(data->main_wnd, &rect);
	return glm::vec2(rect.right - rect.left, rect.bottom - rect.top);
}

glm::vec2 Platform::GetPosition() {
	if(!initialized) return glm::vec2(0);
	RECT rect;
	GetWindowRect(data->main_wnd, &rect);
	return glm::vec2(rect.left, rect.top);
}

PlatformChildWindow::PlatformChildWindow(std::wstring title, int width, int height) {
	if(!Platform::IsInitiallized()) {
		throw new std::exception("Platform not initialized");
	}
	data = new PlatformSpecificData();
	data->wnd_class = Platform::data->wnd_class;
	data->main_wnd = CreateWindowW(L"WAG", title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, width, height, nullptr, nullptr, GetModuleHandle(NULL), nullptr);
	if (!data->main_wnd) {
		throw new std::exception("Failed to create window");
	}
	ShowWindow(data->main_wnd, SW_SHOWNORMAL);
	UpdateWindow(data->main_wnd);
}

PlatformChildWindow::~PlatformChildWindow() {
	ShowWindow(data->main_wnd, SW_HIDE);
	DestroyWindow(data->main_wnd);
	delete data;
}

void PlatformChildWindow::Show(bool show) {
	ShowWindow(Platform::data->main_wnd, show ? SW_SHOWNORMAL : SW_HIDE);
}

void PlatformChildWindow::SetTitle(std::wstring title) {
	SetWindowTextW(data->main_wnd, title.c_str());
}

std::wstring PlatformChildWindow::GetTitle() {
	wchar_t buf[256];
	GetWindowTextW(data->main_wnd, buf, 256);
	return buf;
}

void PlatformChildWindow::SetSize(int width, int height) {
	RECT rect;
	GetWindowRect(data->main_wnd, &rect);
	MoveWindow(data->main_wnd, rect.left, rect.top, width, height, TRUE);
}

void PlatformChildWindow::SetPosition(int x, int y) {
	RECT rect;
	GetWindowRect(data->main_wnd, &rect);
	MoveWindow(data->main_wnd, x, y, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

glm::vec2 PlatformChildWindow::GetSize() {
	RECT rect;
	GetClientRect(data->main_wnd, &rect);
	return glm::vec2(rect.right - rect.left, rect.bottom - rect.top);
}

glm::vec2 PlatformChildWindow::GetPosition() {
	RECT rect;
	GetWindowRect(data->main_wnd, &rect);
	return glm::vec2(rect.left, rect.top);
}

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;

		
	}
	return DefWindowProc(wnd, msg, wparam, lparam);
}

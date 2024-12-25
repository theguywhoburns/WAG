#include <WAG/WAG.hpp>
#include <WAG/event.hpp>
#include <WAG/input.hpp>
#include <WAG/platform/Window.hpp>
#include <WAG/platform/platform.hpp>
#include <WAG/util.hpp>
#include <cstdint>
#include <memory>

#if defined(WAG_PLATFORM_WINDOWS)
#include <Windows.h>
#include <Windowsx.h>
namespace WAG::Platform::Win64 {

LRESULT CALLBACK FirstStageWindowProcedure(HWND hWnd, UINT message,
                                           WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WAGWindowProcedure(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam);
class WAG_API Win64Window : public ::WAG::Platform::IWindow {
  friend LRESULT CALLBACK FirstStageWindowProcedure(HWND hWnd, UINT message,
                                                    WPARAM wParam,
                                                    LPARAM lParam);
  friend LRESULT CALLBACK WAGWindowProcedure(HWND hWnd, UINT message,
                                             WPARAM wParam, LPARAM lParam);

  HWND mHWnd;
  int minX = 0, minY = 0;
  DWORD style = 0, exStyle = 0;
  DWORD fullScreenStyle = 0, fullScreenExStyle = 0;

public:
  Win64Window(const char *window_name, uint32_t width, uint32_t height) {
    static bool isPlatformInitialized = false;
    style = WS_OVERLAPPEDWINDOW;
    exStyle = 0;
    fullScreenStyle = WS_OVERLAPPEDWINDOW & ~WS_OVERLAPPEDWINDOW;
    fullScreenExStyle = WS_EX_TOPMOST;

    // Adjust window rect by it's styles
    RECT wr = {0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
    AdjustWindowRect(&wr, style, FALSE);
    mHWnd = CreateWindowEx(exStyle, TEXT("WAGWindowClass"), TEXT(window_name),
                           style, CW_USEDEFAULT, CW_USEDEFAULT,
                           wr.right - wr.left, wr.bottom - wr.top, nullptr,
                           nullptr, GetModuleHandle(nullptr), nullptr);

    reportError(mHWnd != nullptr, "create window");
    SetProp(mHWnd, TEXT("WAGWindow"), reinterpret_cast<HANDLE>(this));
  }
  void show() override {
    if (!IsWindowVisible(mHWnd))
      ShowWindow(mHWnd, SW_SHOW);
  }
  void minimize() override {
    if (IsWindowVisible(mHWnd))
      ShowWindow(mHWnd, SW_MINIMIZE);
  }
  void maximize() override {
    if (!IsZoomed(mHWnd))
      ShowWindow(mHWnd, SW_MAXIMIZE);
  }
  void focus() override {
    if (GetForegroundWindow() != mHWnd)
      SetForegroundWindow(mHWnd);
  }
  bool isMinimized() const override { return IsIconic(mHWnd); }
  bool isMaximized() const override { return IsZoomed(mHWnd); }
  bool isFocused() const override { return GetForegroundWindow() == mHWnd; }
  void setCursorVisible(bool visible = true) override { ShowCursor(visible); }

  void setMouseGrabbed(bool grabbed) override {
    if (grabbed) {
      RECT windowRect;
      GetWindowRect(mHWnd, &windowRect);
      ClipCursor(&windowRect);
    } else {
      ClipCursor(nullptr);
    }
  }

  void setWindowState(WindowState state) override {
    LONG style = GetWindowLong(mHWnd, GWL_STYLE);
    switch (state) {
    case WindowState::Windowed:
      style |= WS_OVERLAPPEDWINDOW;
      break;
    case WindowState::Borderless:
      style &= ~WS_OVERLAPPEDWINDOW;
      break;
    }
    SetWindowLong(mHWnd, GWL_STYLE, style);
  }

  void setFullscreen(bool fullscreen, uint32_t width,
                     uint32_t height) override {
    if (!fullscreen) {
      ChangeDisplaySettings(nullptr, 0);
    }
    if (width == 0 || height == 0) {
      width = GetSystemMetrics(SM_CXSCREEN);
      height = GetSystemMetrics(SM_CYSCREEN);
    }
    DEVMODE dmSettings;
    memset(&dmSettings, 0, sizeof(dmSettings));
    if (!EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dmSettings)) {
      Log<LogLevel::Error>("Could Not Enum Display Settings");
      return;
    }
    dmSettings.dmPelsWidth = width;
    dmSettings.dmPelsHeight = height;
    dmSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    int result = ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN);
    if (result != DISP_CHANGE_SUCCESSFUL) {
      Log<LogLevel::Error>("Display Mode Not Compatible");
      PostQuitMessage(0);
    }
  }

  bool isFullscreen() const override {
    return (GetWindowLong(mHWnd, GWL_STYLE) & WS_OVERLAPPEDWINDOW) == 0;
  }

  bool isOpen() const override { return IsWindow(mHWnd); }

  void setTitle(const std::string &title) override {
    reportError(SetWindowText(mHWnd, title.c_str()),
                "Failed to set window title");
  }

  std::string getTitle() const override {
    char title[MAX_PATH];
    reportError(GetWindowText(mHWnd, title, 256), "Failed to get window title");
    return std::string(title);
  }

  void setMinimumSize(uint32_t width, uint32_t height) override {
    minX = width;
    minY = height;
  }

  void setResizeable(bool resizeable) override {
    LONG style = GetWindowLong(mHWnd, GWL_STYLE);
    if (resizeable) {
      style |= WS_THICKFRAME;
    } else {
      style &= ~WS_THICKFRAME;
    }
    SetWindowLong(mHWnd, GWL_STYLE, style);
  }

  void setSize(uint32_t width, uint32_t height) override {
    RECT rect;
    GetWindowRect(mHWnd, &rect);
    MoveWindow(mHWnd, rect.left, rect.top, width, height, TRUE);
  }

  std::pair<uint32_t, uint32_t> getSize() const override {
    RECT rect;
    GetClientRect(mHWnd, &rect);
    DWORD style = GetWindowLong(mHWnd, GWL_STYLE);
    DWORD exStyle = GetWindowLong(mHWnd, GWL_EXSTYLE);
    AdjustWindowRectEx(&rect, style, FALSE, exStyle);
    return {rect.right - rect.left, rect.bottom - rect.top};
  }

  void setPosition(int32_t x, int32_t y) override {
    MoveWindow(mHWnd, x, y, 0, 0, TRUE);
  }

  std::pair<int32_t, int32_t> getPosition() const override {
    RECT rect;
    GetWindowRect(mHWnd, &rect);
    return {rect.left, rect.top};
  }

  std::pair<uint32_t, uint32_t> getInnerSize() const override {
    RECT rect;
    GetClientRect(mHWnd, &rect);
    return {rect.right, rect.bottom};
  }

  void *getNativeWindow() const override { return mHWnd; }

  ~Win64Window() override {
    DestroyWindow(mHWnd);
    RemoveProp(mHWnd, TEXT("WAGWindow"));
  }

  void setIcon(const char *path, bool setMenu = false) override {
    // Load small and big icons
    HANDLE hSmallIcon =
        LoadImageA(0, path, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    // Report errors and set icons for the main window
    reportError(hSmallIcon != INVALID_HANDLE_VALUE && hSmallIcon != nullptr,
                ("load small icon from file: " + std::string(path)).c_str());
    SendMessage(mHWnd, WM_SETICON, ICON_SMALL, (LPARAM)hSmallIcon);
    // Clean up resources
    if (hSmallIcon)
      DestroyIcon((HICON)hSmallIcon);
  }
};

LRESULT CALLBACK WAGWindowProcedure(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam) {
  Win64::Win64Window *window =
      reinterpret_cast<Win64::Win64Window *>(GetProp(hWnd, TEXT("WAGWindow")));
  using ::WAG::Platform::IWindow;
  Event::Dispatcher platform_dispatcher;
  switch (message) {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_PAINT:
  case WM_NCPAINT:

    break;
  case WM_SIZE:
    platform_dispatcher.dispatch(
        IWindow::ResizeEvent{window, static_cast<uint32_t>(LOWORD(lParam)),
                             static_cast<uint32_t>(HIWORD(lParam))});
    break;
  case WM_MOVE:
    platform_dispatcher.dispatch(
        IWindow::MoveEvent{window, LOWORD(lParam), HIWORD(lParam)});
    break;
  case WM_SETFOCUS:
    platform_dispatcher.dispatch(IWindow::FocusEvent{window, true});
    break;
  case WM_KILLFOCUS:
    platform_dispatcher.dispatch(IWindow::FocusEvent{window, false});
    break;
  case WM_SYSCOMMAND:
    switch (wParam) {
    case SC_MINIMIZE:
      platform_dispatcher.dispatch(IWindow::MinimizeEvent{window});
      break;
    case SC_MAXIMIZE:
      platform_dispatcher.dispatch(IWindow::MaximizeEvent{window});
      break;
    case SC_RESTORE:
      platform_dispatcher.dispatch(IWindow::RestoreEvent{window});
      break;
    }
  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
  case WM_KEYUP:
  case WM_SYSKEYUP: {
    bool down = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
    Input::Key key = Input::Key(static_cast<uint16_t>(wParam % 256));
    bool isExt = (HIWORD(lParam) & KF_EXTENDED) == KF_EXTENDED;
    if (wParam == VK_MENU) {
      key = isExt ? Input::Key::KeyRAlt : Input::Key::KeyLAlt;
    } else if (wParam == VK_SHIFT) {
      uint32_t leftShift = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
      uint32_t scancode = ((lParam & (0xFF << 16)) >> 16);
      key =
          scancode == leftShift ? Input::Key::KeyLShift : Input::Key::KeyRShift;
    } else if (wParam == VK_CONTROL) {
      key = isExt ? Input::Key::KeyRControl : Input::Key::KeyLControl;
    }

    // HACK: This is gross windows keybind crap, from kohi engine
    if (key == VK_OEM_1) {
      key = Input::Key::KeySemicolon;
    }

    platform_dispatcher.dispatch(IWindow::KeyPressEvent{window, key, down});
  } break;
  case WM_GETMINMAXINFO: {
    auto info = reinterpret_cast<MINMAXINFO *>(lParam);
    info->ptMinTrackSize.x = window->minX;
    info->ptMinTrackSize.y = window->minY;
  }
  case WM_LBUTTONDOWN:
  case WM_LBUTTONUP:
  case WM_RBUTTONDOWN:
  case WM_RBUTTONUP:
  case WM_MBUTTONDOWN:
  case WM_MBUTTONUP: {
    bool down = (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN ||
                 message == WM_MBUTTONDOWN);
    Input::MouseButton button = Input::MouseButton(wParam);
    platform_dispatcher.dispatch(
        IWindow::MouseButtonEvent{window, button, down});
  } break;
  case WM_MOUSEMOVE: {
    int x = GET_X_LPARAM(lParam);
    int y = GET_Y_LPARAM(lParam);
    platform_dispatcher.dispatch(IWindow::MouseMoveEvent{window, x, y});
  } break;
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK FirstStageWindowProcedure(HWND hWnd, UINT message,
                                           WPARAM wParam, LPARAM lParam) {
  if (message == WM_NCCREATE) {
    SetWindowLongPtr(hWnd, GWLP_WNDPROC,
                     reinterpret_cast<LONG_PTR>(&WAGWindowProcedure));
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}
}; // namespace WAG::Platform::Win64

namespace WAG::Platform {
// Just a caller for the event dispatcher
static ::WAG::Event::Dispatcher platform_dispatcher;
void IWindow::Update() {
  MSG msg;
  while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

::std::unique_ptr<IWindow> IWindow::Create(const char *window_name,
                                           uint32_t width, uint32_t height,
                                           const char *iconPath) {
  static bool isPlatformInitialized = false;
  if (!isPlatformInitialized) {
    WNDCLASSEX wc = {sizeof(WNDCLASSEX)};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = Win64::FirstStageWindowProcedure;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = TEXT("WAGWindowClass");
    wc.hIcon = static_cast<HICON>(LoadImageA(GetModuleHandle(nullptr), iconPath,
                                             IMAGE_ICON, 0, 0,
                                             LR_LOADFROMFILE | LR_DEFAULTSIZE));
    wc.hIconSm =
        static_cast<HICON>(LoadImageA(GetModuleHandle(nullptr), iconPath,
                                      IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName = nullptr;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    auto res = RegisterClassEx(&wc);
    reportError(res != 0 || GetLastError() == ERROR_CLASS_ALREADY_EXISTS,
                "register window class");
    isPlatformInitialized = true;
  }
  return ::std::make_unique<::WAG::Platform::Win64::Win64Window>(window_name,
                                                                 width, height);
}

WAG_API std::tuple<uint32_t, uint32_t> getScreenResolution() {
  RECT desktop;
  const HWND hDesktop = GetDesktopWindow();
  if (!GetWindowRect(hDesktop, &desktop)) {
    reportError(false, "Failed to get desktop rect");
  }
  return {static_cast<uint32_t>(desktop.right),
          static_cast<uint32_t>(desktop.bottom)};
}

WAG_API float getScreenDpi() {
  HDC screen = GetDC(nullptr);
  reportError(screen != nullptr, "Failed to get screen DC");
  int dpiX = GetDeviceCaps(screen, LOGPIXELSX);
  ReleaseDC(nullptr, screen);
  reportError(dpiX != 0, "Failed to get screen DPI");
  return static_cast<float>(dpiX);
}
}; // namespace WAG::Platform

#endif // defined(WAG_PLATFORM_WINDOWS)
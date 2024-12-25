#pragma once
#include "WAG/input.hpp"
#include <WAG/platform/platform.hpp>

#include <memory>
#include <string>
#include <utility>

namespace WAG::Platform {
WAG_API std::tuple<uint32_t, uint32_t> getScreenResolution();
WAG_API float getScreenDpi();
class WAG_API IWindow {
public:
  struct BaseEvent {
    IWindow *window;
  };
  struct ResizeEvent : BaseEvent {
    uint32_t width, height;
  };
  struct MoveEvent : BaseEvent {
    int32_t x, y;
  };
  struct CloseEvent : BaseEvent {};
  struct FocusEvent : BaseEvent {
    bool focused;
  };
  struct MinimizeEvent : BaseEvent {};
  struct MaximizeEvent : BaseEvent {};
  struct RestoreEvent : BaseEvent {};
  struct CreateEvent : BaseEvent {};
  struct KeyPressEvent : BaseEvent {
    ::WAG::Input::Key key;
    bool pressed;
  };
  struct MouseButtonEvent : BaseEvent {
    Input::MouseButton button;
    bool pressed;
  };
  struct MouseMoveEvent : BaseEvent {
    int x, y;
  };

  enum class WindowState : uint8_t { Windowed = 0, Borderless };
  static void Update();
  static ::std::unique_ptr<IWindow> Create(const char *window_name,
                                           uint32_t width, uint32_t height,
                                           const char *iconPath);
  virtual bool isOpen() const = 0;
  virtual void show() = 0;
  virtual void minimize() = 0;
  virtual void maximize() = 0;
  virtual void focus() = 0;
  virtual bool isMinimized() const = 0;
  virtual bool isMaximized() const = 0;
  virtual bool isFocused() const = 0;
  virtual void setCursorVisible(bool visible = true) = 0;
  virtual void setMouseGrabbed(bool grabbed) = 0;
  virtual void setWindowState(WindowState state) = 0;
  virtual void setFullscreen(bool fullscreen, uint32_t width = 0,
                             uint32_t height = 0) = 0;
  virtual bool isFullscreen() const = 0;
  virtual void setTitle(const std::string &title) = 0;
  virtual std::string getTitle() const = 0;
  virtual void setMinimumSize(uint32_t width, uint32_t height) = 0;
  virtual void setResizeable(bool resizeable) = 0;
  virtual void setSize(uint32_t width, uint32_t height) = 0;
  virtual std::pair<uint32_t, uint32_t> getSize() const = 0;
  virtual void setPosition(int32_t x, int32_t y) = 0;
  virtual std::pair<int32_t, int32_t> getPosition() const = 0;
  virtual std::pair<uint32_t, uint32_t> getInnerSize() const = 0;
  virtual void *getNativeWindow() const = 0;
  virtual void setIcon(const char *path, bool setMenu = false) = 0;
  virtual ~IWindow() = default;
};
}; // namespace WAG::Platform
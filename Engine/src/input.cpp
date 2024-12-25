#include <WAG/WAG.hpp>
#include <WAG/event.hpp>
#include <WAG/input.hpp>
#include <WAG/platform/Window.hpp>
#include <WAG/platform/platform.hpp>

namespace WAG::Input {
InputSystem::InputSystem() {
  auto disp = Event::Dispatcher();
  this->mKeyPressEventId = disp.addListener<Platform::IWindow::KeyPressEvent>(
      [&](const auto &event) {
        auto key = event.key;
        auto pressed = event.pressed;
        this->mKeys[key] = pressed;
      });

  this->mMousePressEventId =
      disp.addListener<Platform::IWindow::MouseButtonEvent>(
          [&](const auto &event) {
            auto button = event.button;
            auto pressed = event.pressed;
            this->mMouseButtons[button] = pressed;
          });

  this->mMouseMoveEventId = disp.addListener<Platform::IWindow::MouseMoveEvent>(
      [&](const auto &event) {
        this->mMouseDeltaX = event.x - this->mMouseX;
        this->mMouseDeltaY = event.y - this->mMouseY;
        this->mMouseX = event.x;
        this->mMouseY = event.y;
      });
}

InputSystem::~InputSystem() {
  auto disp = Event::Dispatcher();
  disp.removeListener<Platform::IWindow::KeyPressEvent>(this->mKeyPressEventId);
  disp.removeListener<Platform::IWindow::MouseButtonEvent>(
      this->mMousePressEventId);
  disp.removeListener<Platform::IWindow::MouseMoveEvent>(
      this->mMouseMoveEventId);
}

void InputSystem::Update() {
  std::copy(this->mKeys, this->mKeys + Key::KeyMAX, this->mOldKeys);
  std::copy(this->mMouseButtons, this->mMouseButtons + MouseButton::MouseMAX,
            this->mOldMouseButtons);
}
bool InputSystem::getKey(Key key) {
  return this->mKeys[static_cast<size_t>(key)];
}

bool InputSystem::getKeyDown(Key key) {
  return this->mKeys[static_cast<size_t>(key)] &&
         !this->mOldKeys[static_cast<size_t>(key)];
}

bool InputSystem::getKeyUp(Key key) {
  return this->mKeys[static_cast<size_t>(key)] &&
         this->mOldKeys[static_cast<size_t>(key)];
}
bool InputSystem::getMouseButton(MouseButton button) {
  return this->mMouseButtons[static_cast<size_t>(button)];
}

bool InputSystem::getMouseButtonDown(MouseButton button) {
  return this->mMouseButtons[static_cast<size_t>(button)] &&
         !this->mOldMouseButtons[static_cast<size_t>(button)];
}

bool InputSystem::getMouseButtonUp(MouseButton button) {
  return !this->mMouseButtons[static_cast<size_t>(button)] &&
         this->mOldMouseButtons[static_cast<size_t>(button)];
}

int InputSystem::getMouseX() { return this->mMouseX; }

int InputSystem::getMouseY() { return this->mMouseY; }

std::tuple<int, int> InputSystem::getMousePosition() {
  return std::make_tuple(this->mMouseX, this->mMouseY);
}

int InputSystem::getMouseDeltaX() { return this->mMouseDeltaX; }

int InputSystem::getMouseDeltaY() { return this->mMouseDeltaY; }

std::tuple<int, int> InputSystem::getMouseDelta() {
  return std::make_tuple(this->mMouseDeltaX, this->mMouseDeltaY);
}
} // namespace WAG::Input
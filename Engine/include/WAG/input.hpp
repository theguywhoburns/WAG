#pragma once
#include <WAG/WAG.hpp>
#include <cstddef>
#include <cstdint>
#include <tuple>
namespace WAG::Input {
enum MouseButton : uint16_t {
  MouseLeft = 0,
  MouseMiddle = 1,
  MouseRight = 2,
  MouseMAX
};
enum Key : uint16_t {
  KeyBackspace = 0x08,
  KeyEnter = 0x0D,
  KeyTab = 0x09,
  KeyShift = 0x10,
  KeyControl = 0x11,
  KeyPause = 0x13,
  KeyCapital = 0x14,
  KeyEscape = 0x1B,
  KeyConvert = 0x1C,
  KeyNonConvert = 0x1D,
  KeyAccept = 0x1E,
  KeyModeChange = 0x1F,
  KeySpace = 0x20,
  KeyPageUp = 0x21,
  KeyPageDown = 0x22,
  KeyEnd = 0x23,
  KeyHome = 0x24,
  KeyLeft = 0x25,
  KeyUp = 0x26,
  KeyRight = 0x27,
  KeyDown = 0x28,
  KeySelect = 0x29,
  KeyPrint = 0x2A,
  KeyExecute = 0x2B,
  KeyPrintScreen = 0x2C,
  KeyInsert = 0x2D,
  KeyDelete = 0x2E,
  KeyHelp = 0x2F,
  Key_0 = 0x30,
  Key_1 = 0x31,
  Key_2 = 0x32,
  Key_3 = 0x33,
  Key_4 = 0x34,
  Key_5 = 0x35,
  Key_6 = 0x36,
  Key_7 = 0x37,
  Key_8 = 0x38,
  Key_9 = 0x39,
  KeyA = 0x41,
  KeyB = 0x42,
  KeyC = 0x43,
  KeyD = 0x44,
  KeyE = 0x45,
  KeyF = 0x46,
  KeyG = 0x47,
  KeyH = 0x48,
  KeyI = 0x49,
  KeyJ = 0x4A,
  KeyK = 0x4B,
  KeyL = 0x4C,
  KeyM = 0x4D,
  KeyN = 0x4E,
  KeyO = 0x4F,
  KeyP = 0x50,
  KeyQ = 0x51,
  KeyR = 0x52,
  KeyS = 0x53,
  KeyT = 0x54,
  KeyU = 0x55,
  KeyV = 0x56,
  KeyW = 0x57,
  KeyX = 0x58,
  KeyY = 0x59,
  KeyZ = 0x5A,
  KeyLeftSuper = 0x5B,
  KeyRightSuper = 0x5C,
  KeyApps = 0x5D,
  KeySleep = 0x5F,
  KeyNumpad0 = 0x60,
  KeyNumpad1 = 0x61,
  KeyNumpad2 = 0x62,
  KeyNumpad3 = 0x63,
  KeyNumpad4 = 0x64,
  KeyNumpad5 = 0x65,
  KeyNumpad6 = 0x66,
  KeyNumpad7 = 0x67,
  KeyNumpad8 = 0x68,
  KeyNumpad9 = 0x69,
  KeyMultiply = 0x6A,
  KeyAdd = 0x6B,
  KeySeparator = 0x6C,
  KeySubtract = 0x6D,
  KeyDecimal = 0x6E,
  KeyDivide = 0x6F,
  KeyF1 = 0x70,
  KeyF2 = 0x71,
  KeyF3 = 0x72,
  KeyF4 = 0x73,
  KeyF5 = 0x74,
  KeyF6 = 0x75,
  KeyF7 = 0x76,
  KeyF8 = 0x77,
  KeyF9 = 0x78,
  KeyF10 = 0x79,
  KeyF11 = 0x7A,
  KeyF12 = 0x7B,
  KeyF13 = 0x7C,
  KeyF14 = 0x7D,
  KeyF15 = 0x7E,
  KeyF16 = 0x7F,
  KeyF17 = 0x80,
  KeyF18 = 0x81,
  KeyF19 = 0x82,
  KeyF20 = 0x83,
  KeyF21 = 0x84,
  KeyF22 = 0x85,
  KeyF23 = 0x86,
  KeyF24 = 0x87,
  KeyNumLock = 0x90,
  KeyScroll = 0x91,
  KeyNumpadEqual = 0x92,
  KeyLShift = 0xA0,
  KeyRShift = 0xA1,
  KeyLControl = 0xA2,
  KeyRControl = 0xA3,
  KeyLAlt = 0xA4,
  KeyRAlt = 0xA5,
  KeySemicolon = 0x3B,
  KeyApostrophe = 0xDE,
  KeyQuote = KeyApostrophe,
  KeyEqual = 0xBB,
  KeyComma = 0xBC,
  KeyMinus = 0xBD,
  KeyPeriod = 0xBE,
  KeySlash = 0xBF,
  KeyGrave = 0xC0,
  KeyLBracket = 0xDB,
  KeyPipe = 0xDC,
  KeyBackslash = KeyPipe,
  KeyRBracket = 0xDD,
  KeyMAX = 0xFF // Max key value
}; // namespace WAG::Input

class InputSystem {
public:
  static InputSystem &get() {
    static InputSystem instance;
    return instance;
  }

  bool getKey(Key key);
  bool getKeyDown(Key key);
  bool getKeyUp(Key key);

  bool getMouseButton(MouseButton button);
  bool getMouseButtonDown(MouseButton button);
  bool getMouseButtonUp(MouseButton button);

  int getMouseX();
  int getMouseY();
  ::std::tuple<int, int> getMousePosition();
  int getMouseDeltaX();
  int getMouseDeltaY();
  ::std::tuple<int, int> getMouseDelta();

private:
  bool mKeys[static_cast<size_t>(Key::KeyMAX)];
  bool mOldKeys[static_cast<size_t>(Key::KeyMAX)];
  bool mMouseButtons[static_cast<size_t>(MouseButton::MouseMAX)];
  bool mOldMouseButtons[static_cast<size_t>(MouseButton::MouseMAX)];
  int mMouseX;
  int mMouseY;
  int mMouseDeltaX;
  int mMouseDeltaY;

private:
  InputSystem();
  ~InputSystem();
  InputSystem(const InputSystem &) = delete;
  InputSystem(InputSystem &&) = delete;
  InputSystem &operator=(const InputSystem &) = delete;
  InputSystem &operator=(InputSystem &&) = delete;

  friend class WAG::Engine;

  void Update();

  size_t mKeyPressEventId;
  size_t mMousePressEventId;
  size_t mMouseMoveEventId;
};
}; // namespace WAG::Input
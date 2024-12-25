#include <WAG/WAG.hpp>
#include <WAG/platform/platform.hpp>
#include <WAG/util.hpp>
#include <string>

#if defined(WAG_PLATFORM_WINDOWS)
#include <Windows.h>
namespace WAG::Platform {
static std::string ErrorAsString(DWORD errorMessageID) {
  if (errorMessageID == 0) {
    return std::string(); // No error message has been recorded
  }

  LPSTR messageBuffer = nullptr;

  // Ask Win64 to give us the string version of that message ID.
  // The parameters we pass in, tell Win64 to create the buffer that holds the
  // message for us (because we don't yet know how long the message string will
  // be).
  size_t size = FormatMessageA(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPSTR)&messageBuffer, 0, NULL);

  // Copy the error message into a std::string.
  std::string message(messageBuffer, size);

  // Free the Win64's string's buffer.
  LocalFree(messageBuffer);

  return message;
}

void reportError(bool cond, const char *msg) {
  if (!cond) {
    auto errorMessageID = GetLastError();
    Log<LogLevel::Debug>("Error code: ", errorMessageID);
    auto errStr = ErrorAsString(errorMessageID);
    Log<LogLevel::Error>("Failed to ", msg, ": ", errStr.c_str());
    throw std::runtime_error("Failed to " + std::string(msg) + ": " + errStr);
  }
}

}; // namespace WAG::Platform
#endif // defined(WAG_PLATFORM_WINDOWS)
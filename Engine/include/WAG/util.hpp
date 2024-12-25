#pragma once

#include <WAG/WAG.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace WAG::Util {

template <auto Min, auto Max,
          typename T = std::common_type_t<decltype(Min), decltype(Max)>>
class WAG_API RangeValue {
public:
  constexpr RangeValue(T value) : mValue(value) {
    if (mValue < Min || mValue > Max) {
      throw std::out_of_range("Value is out of range");
    }
  }
  constexpr T value() const { return mValue; }
  constexpr T &operator=(T value) {
    if (value < Min || value > Max) {
      throw std::out_of_range("Value is out of range");
    }
    mValue = value;
    return mValue;
  }

private:
  T mValue;
};

namespace Console {
struct WAG_API RGB {
  RangeValue<0, 255, uint8_t> r;
  RangeValue<0, 255, uint8_t> g;
  RangeValue<0, 255, uint8_t> b;
};

enum class ConsoleLayer : int { Background = 48, Foreground = 38, Both };

WAG_API std::string getColorStr(const RGB &rgb,
                                ConsoleLayer layer = ConsoleLayer::Foreground);
WAG_API void resetColor();
WAG_API std::string resetColorStr();
WAG_API void clearScreen();
}; // namespace Console

namespace Logger {
enum LogLevel : int { Fatal = 0, Error, Warning, Info, Debug, Trace };
#if _FULL_DEBUG || _TRACE
inline constexpr LogLevel currentLogLevel = LogLevel::Trace;
#elif _DEBUG
inline constexpr LogLevel currentLogLevel = LogLevel::Debug;
#else
inline constexpr LogLevel currentLogLevel = LogLevel::Info;
#endif
template <LogLevel level = LogLevel::Info, typename... Args>
WAG_API inline void Log(Args &&...args) {
  using namespace Console;
  static constexpr std::tuple<RGB, RGB, const char *> logLevelColors[] = {
      {{255, 0, 0}, {255, 0, 0}, "[FATAL]: "},   // Fatal
      {{0, 0, 0}, {255, 0, 0}, "[Error]: "},     // Error
      {{0, 0, 0}, {255, 165, 0}, "[Warning]: "}, // Warning
      {{0, 0, 0}, {0, 255, 255}, "[Info]: "},    // Info
      {{0, 0, 0}, {0, 255, 0}, "[Debug]: "},     // Debug
      {{0, 0, 0}, {0, 0, 255}, "[Trace]: "}      // Trace
  };

  if constexpr (level <= currentLogLevel) {
    auto [bg, fg, levelStr] = logLevelColors[static_cast<size_t>(level)];
    std::stringstream oss;
    (oss << ... << args);
    std::cout << getColorStr(fg, ConsoleLayer::Foreground)
              << getColorStr(bg, ConsoleLayer::Background) << oss.str()
              << resetColorStr() << std::endl;
  }
}

template <LogLevel level = LogLevel::Info, typename... Args>
WAG_API inline void FLog(std::ofstream &handle, bool decorated,
                         Args &&...args) {
  using namespace Console;
  static constexpr std::tuple<RGB, RGB, const char *> logLevelColors[] = {
      {{255, 0, 0}, {255, 0, 0}, "[FATAL]: "},   // Fatal
      {{0, 0, 0}, {255, 0, 0}, "[Error]: "},     // Error
      {{0, 0, 0}, {255, 165, 0}, "[Warning]: "}, // Warning
      {{0, 0, 0}, {0, 255, 255}, "[Info]: "},    // Info
      {{0, 0, 0}, {0, 255, 0}, "[Debug]: "},     // Debug
      {{0, 0, 0}, {0, 0, 255}, "[Trace]: "}      // Trace
  };

  if constexpr (level <= currentLogLevel) {
    auto [bg, fg, levelStr] = logLevelColors[static_cast<size_t>(level)];
    std::stringstream oss;
    if (decorated) {
      oss << getColorStr(fg, ConsoleLayer::Foreground)
          << getColorStr(bg, ConsoleLayer::Background) << levelStr;
    }
    (oss << ... << args);
    if (decorated) {
      oss << resetColorStr();
    }
    handle << oss.str() << std::endl;
  }
}
}; // namespace Logger
}; // namespace WAG::Util

// HACK: Get rid of this
namespace WAG {
using ::WAG::Util::Logger::FLog;
using ::WAG::Util::Logger::Log;
using ::WAG::Util::Logger::LogLevel;
}; // namespace WAG
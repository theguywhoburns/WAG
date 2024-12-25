#pragma once
#include <cstdint>
#include <memory>
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)
#if !defined(_WIN64) && !defined(__WIN64) && !defined(__WIN64__)
#error "Only windows 64 bit is supported"
#endif // !defined(_WIN64)
#define WAG_PLATFORM_WINDOWS 1
#elif defined(__linux__) || defined(__gnu_linux__) || defined(__linux) ||      \
    defined(__unix__)
#define WAG_PLATFORM_LINUX 1
#elif defined(__APPLE__) || defined(__MACH__) || defined(__macos__) ||         \
    defined(__MACOSX)
#define WAG_PLATFORM_MACOS 1
#else
#error "Unsupported platform"
#endif

#if defined(_MSC_VER)
#if defined(WAX_EXPORTS)
#define WAG_API __declspec(dllexport)
#else
#define WAG_API __declspec(dllimport)
#endif
#else
#if defined(WAX_EXPORTS)
#define WAG_API __attribute__((visibility("default")))
#else
#define WAG_API
#endif
#endif

namespace WAG {
namespace Platform {
class WAG_API IWindow;

}; // namespace Platform
class WAG_API EngineConfig {
public:
  const char *name;
  const uint32_t width = 1024, height = 768;
}; // class WAG_API EngineConfig

class WAG_API Engine {
public:
  Engine(EngineConfig config = {.name = "WAG", .width = 1024, .height = 768});
  int run();
  ~Engine();

private:
  ::std::unique_ptr<Platform::IWindow> mWindow;
}; // class WAG_API Engine
}; // namespace WAG
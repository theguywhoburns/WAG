#pragma once
#include <WAG/WAG.hpp>
#include <WAG/event.hpp>
#include <WAG/input.hpp>

// Platform specific implementations are isolated
namespace WAG::Platform {
enum class PlatformType { Windows, Linux, MacOS };
class WAG_API IWindow;  // Window interface
class WAG_API ILibrary; // dll/so/etc... interface
// TODO: implement this
class WAG_API IFileSystem; // File system interface
// TODO: implement this
class WAG_API INetwork; // Network interface

#if defined(WAG_PLATFORM_WINDOWS)
constexpr PlatformType platform = PlatformType::Windows;
#elif defined(WAG_PLATFORM_LINUX)
constexpr PlatformType platform = PlatformType::Linux;
#elif defined(WAG_PLATFORM_MACOS)
constexpr PlatformType platform = PlatformType::MacOS;
#endif

/// \note DO NOT USE THIS, THIS ONE IS FOR INTERNAL ERROR REPORT AND TO GET RID
/// OF BOILERPLATE CODE
void reportError(bool cond, const char *msg);

}; // namespace WAG::Platform
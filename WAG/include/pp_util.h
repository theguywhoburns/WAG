#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Compiler detection
#if defined(__GNUC__) && !defined(__clang__)
    // GNU Compiler Collection
    #define COMPILER_GNU 1
#elif defined(_MSC_VER)
    // Microsoft Visual Studio
    #define COMPILER_MSVC 1
#elif defined(__clang__)
    // Clang/LLVM
    #define COMPILER_CLANG 1
#elif defined(__INTEL_COMPILER) || defined(__ICL)
    // Intel Compiler
    #define COMPILER_INTEL 1
#elif defined(__SUNPRO_C)
    // Oracle Solaris Studio (formerly Sun Studio)
    #define COMPILER_SUN 1
#elif defined(__EMSCRIPTEN__)
    // Emscripten (WebAssembly/JS)
    #define COMPILER_EMSCRIPTEN 1
#elif defined(__WATCOMC__)
    // Watcom C Compiler
    #define COMPILER_WATCOM 1
#elif defined(__TINYC__)
    // Tiny C Compiler (TCC)
    #define COMPILER_TINYC 1
#elif defined(__BORLANDC__)
    // Borland C++ Compiler
    #define COMPILER_BORLAND 1
#elif defined(__PGI)
    // Portland Group Compiler (PGI)
    #define COMPILER_PGI 1
#elif defined(__xlC__)
    // IBM XL C/C++ Compiler
    #define COMPILER_XLC 1
#elif defined(__HP_cc)
    // HP C/aC++ Compiler
    #define COMPILER_HP 1
#else
    #error "Unknown compiler!"
#endif

// Typeof handling based on compiler features
#if defined(COMPILER_GNU) || defined(COMPILER_CLANG) || defined(COMPILER_INTEL) || defined(COMPILER_SUN) || defined(COMPILER_EMSCRIPTEN)
    // GNU and Clang support __typeof__
    #define PP_TYPEOF(x) __typeof__(x)

#elif defined(COMPILER_MSVC) || defined(COMPILER_WATCOM) || defined(COMPILER_BORLAND) || defined(COMPILER_HP)
    // Microsoft Visual Studio doesn't have typeof, so use decltype
    // Watcom doesn't support typeof, fallback to decltype (C++ only)
    // Borland C++ Compiler doesn't support typeof, fallback to decltype
    // HP C/aC++ Compiler doesn't support typeof, fallback to decltype
    #define PP_TYPEOF(x) decltype(x)
#elif defined(COMPILER_TINYC) || defined(COMPILER_PGI) || defined(COMPILER_XLC)
    // Tiny C, PGI, and XLC Compilers support typeof
    #define PP_TYPEOF(x) typeof(x)
#else
    #error "Unknown compiler for typeof!"
#endif

#if COMPILER_GNU || COMPILER_CLANG
    #define packed __attribute__((packed))
    #define align(x) __attribute__((aligned(x)))
    #define inline __attribute__((always_inline))
    #define noret __attribute__((noreturn))
    #define dllexp __attribute__((visibility("default")))
    /* There is no __declspec(dllimport) alternative on gcc/clang */
    #define dllimp 
    #define deprec(msg) __attribute__((deprecated(msg)))
#elif COMPILER_MSVC
    #define packed
    #define align(x) __declspec(align(x))
    #define inline __declspec(forceinline)
    #define noreturn __declspec(noreturn)
    #define dllexp __declspec(dllexport)
    #define dllimp __declspec(dllimport)
    #define deprec(msg) __declspec(deprecated(msg))
#endif

#define PP_UNWRAP(x) x
#define PP_STRINGIFY_(x) #x
#define PP_STRINGIFY(x) PP_STRINGIFY_(x)
#define PP_CONCAT_(a, b) a##b
#define PP_CONCAT(a, b) PP_CONCAT_(a, b)
#define PP_CONCAT_N(...) PP_OVERLOAD(PP_CONCAT)
/// i mofied it... but @author https://gist.github.com/aprell/3722962
#if COMPILER_GNU || COMPILER_CLANG
// Supports 0-128 arguments
#define PP_NARG_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, N, ...) N
// ## deletes preceding comma if _VA_ARGS__ is empty (GCC, Clang)
#define PP_NARG(...) PP_NARG_IMPL(_, ##__VA_ARGS__, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#else
#define PP_NARG_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, N, ...) N
// ## deletes preceding comma if _VA_ARGS__ is empty (GCC, Clang)
#define PP_NARG(...) PP_NARG_IMPL(__VA_ARGS__, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "64-bit is required on Windows!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    // Linux OS
    #define PLATFORM_LINUX 1
    #if defined(__ANDROID__)
        // Android on Linux
        #define PLATFORM_ANDROID 1
    #endif
#elif defined(__unix__)
    // Unix OS (Catch anything not caught by the above)
    #define PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
    // POSIX-compliant systems
    #define PLATFORM_POSIX 1
#elif defined(__APPLE__)
    // Apple platforms
    #define PLATFORM_APPLE 1
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
        #define PLATFORM_IOS 1
        #define PLATFORM_IOS_SIMULATOR 1
    #elif TARGET_OS_IPHONE
        // iOS device
        #define PLATFORM_IOS 1
    #elif TARGET_OS_MAC
        // MacOS device
        #define PLATFORM_MACOS 1
    #else
        #error "Unknown Apple platform"
    #endif
#elif defined(__CYGWIN__)
    // Cygwin environment (POSIX on Windows)
    #define PLATFORM_CYGWIN 1
#elif defined(__MINGW32__) || defined(__MINGW64__)
    // MinGW (Minimal GNU for Windows)
    #define PLATFORM_MINGW 1
    #if defined(__MINGW64__)
        #define PLATFORM_MINGW64 1
    #else
        #define PLATFORM_MINGW32 1
    #endif
#elif defined(__MSYS__)
    // MSYS (Minimal System for Windows)
    #define PLATFORM_MSYS 1
#elif defined(__FreeBSD__)
    // FreeBSD OS
    #define PLATFORM_FREEBSD 1
#elif defined(__OpenBSD__)
    // OpenBSD OS
    #define PLATFORM_OPENBSD 1
#elif defined(__NetBSD__)
    // NetBSD OS
    #define PLATFORM_NETBSD 1
#elif defined(__DragonFly__)
    // DragonFly BSD OS
    #define PLATFORM_DRAGONFLY 1
#elif defined(__HAIKU__)
    // Haiku OS (BeOS-inspired)
    #define PLATFORM_HAIKU 1
#else
    #error "Unknown platform!"
#endif

#define PP_OVERLOAD(f, ...) PP_CONCAT(f, PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define PP_ANON_STRUCT(...) struct { __VA_ARGS__ }
#define PP_ANON_UNION(...) union { __VA_ARGS__ }
#define PP_ANON_ENUM(...) enum { __VA_ARGS__ }
#define PP_TSTRUCT(TSTRUCT_NAME) typedef struct TSTRUCT_NAME TSTRUCT_NAME
#define PP_TUNION(TUNION_NAME) typedef union TUNION_NAME TUNION_NAME
#define PP_TENUM(TENUM_NAME) typedef enum TENUM_NAME TENUM_NAME
#define PP_TFUNC(__type, __name, ...) typedef __type (*__name)(__VA_ARGS__)
#define PP_FUNCCAST(__type, ...) __type(*)(__VA_ARGS__)
#define PP_VERSION_COMPOSE(major, minor, patch) (((major) << 16) | ((minor) << 8) | (patch))
#define PP_VERSION_MAJOR(version) ((version) >> 16)
#define PP_VERSION_MINOR(version) (((version) >> 8) & 0xFF)
#define PP_VERSION_PATCH(version) ((version) & 0xFF)
#define PP_DEPRECATED(msg) deprec(msg)
#define PP_PRAGMA(msg) _Pragma(msg)

#if PPC_EXPORT
#define PP_EXPORT dllexp
#else
#define PP_EXPORT dllimp
#endif

#define WAG_API PP_EXPORT
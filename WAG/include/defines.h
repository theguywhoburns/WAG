#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _MSC_VER 
#define STATIC_ASSERT(expr) _STATIC_ASSERT(expr)
#else
#define STATIC_ASSERT static_assert(expr, msg)
#endif

// Inlining
#if defined(__clang__)
#define INLINE [[gnu::always_inline]] [[gnu::gnu_inline]] extern inline

#elif defined(__GNUC__)
#define INLINE [[gnu::always_inline]] inline

#elif defined(_MSC_VER)
#pragma warning(error: 4714)
#define INLINE __forceinline

#else
#error Unsupported compiler
#endif

#define BIT(x) (1 << x)
#if defined(_MSC_VER)
#ifdef WAG_EXPORT
#define WAG_API __declspec(dllexport)
#else
#define WAG_API __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#ifdef WAG_EXPORT
#define WAG_API __attribute__((visibility("default")))   
#else
#define WAG_API
#endif
#endif

#define NO_VTABLE __declspec(novtable)

#if defined(_WIN32) || defined(_WIN64) 
		#if !defined(_WIN64)
		#error "Only 64-bit Windows is supported"
		#endif
    #define PLATFORM_WINDOWS
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_WINDOWS_CYGWIN
#elif defined(__ANDROID__)
    #define PLATFORM_ANDROID
#elif defined(__linux__)
    // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
    #define PLATFORM_LINUX
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
        #define PLATFORM_BSD
    #endif
#elif defined(__hpux)
    #define PLATFORM_HP_UX
#elif defined(_AIX)
    // IBM AIX
    #define PLATFORM_AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        // Apple IOS
        #define PLATFORM_APPLE_IOS
    #elif TARGET_OS_IPHONE == 1
        // Apple IOS
        #define PLATFORM_APPLE_IOS
    #elif TARGET_OS_MAC == 1
        // Apple OSX
        #define PLATFORM_APPLE_OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    // Oracle(the ones that created java) Solaris, Open Indiana
    #define PLATFORM_SOLARIS
#else
    #error UNKNOWN OR UNSUPPORTED PLATFORM... PEASE USE SUPPORTED ONE 
#endif

STATIC_ASSERT(sizeof(void*) == sizeof(uintptr_t));
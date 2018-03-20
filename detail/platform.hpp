#pragma once

//------------------------------------------------------------------------------

#ifndef app_debug
    #if defined(DEBUG) || defined(_DEBUG)
        #define app_debug 1
    #elif defined(__GNUC__) && !defined(__OPTIMIZE)
        #define app_debug 1
    #endif
#endif

//------------------------------------------------------------------------------
// app_concat(x,y)
//
// Concatenate the macro-expanded results of arguments x and y.
//
#define  app_concat(x,y) _app_concat(x,y)
#define _app_concat(x,y) x##y

//------------------------------------------------------------------------------
// app_quote(x)
//
// Surround the macro-expanded result of argument x in quotes.
//
#define  app_quote(x) _app_quote(x)
#define _app_quote(x) #x

//------------------------------------------------------------------------------

#if defined(__clang__)

    #define app_compiler_id     clang
    #define app_compiler_name   "Clang " __clang_version__
    #define app_compiler_clang  \
        (__clang_major__*10000+__clang_minor__*100+__clang_patchlevel__)

#elif defined(__GNUC__)

    #define app_compiler_id    gcc
    #define app_compiler_name  "GCC " __VERSION__
    #define app_compiler_gcc   \
        (__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)

#elif defined(_MSC_VER)

    #define app_compiler_id    msvc
    #define app_compiler_name  "MSVC " app_quote(_MSC_FULL_VER)
    #define app_compiler_msvc  (_MSC_VER)

#else

    #error "unrecognized compiler"

#endif

//------------------------------------------------------------------------------

#if defined(__ANDROID__)

    #define app_os_android    1
    #define app_os_id         android
    #define app_os_name       "Android"

#elif defined(__linux)

    #define app_os_linux      1
    #define app_os_id         linux
    #define app_os_name       "Linux"

#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)

    #define app_os_apple      1
    #define app_os_ios        1
    #define app_os_id         ios
    #define app_os_name       "iOS"

#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)

    #define app_os_apple      1
    #define app_os_macos      1
    #define app_os_id         macos
    #define app_os_name       "macOS"

#elif __cplusplus_winrt

    #define app_os_microsoft  1
    #define app_os_winrt      1
    #define app_os_id         winrt
    #define app_os_name       "WinRT"

#elif defined(_WIN32)

    #define app_os_microsoft  1
    #define app_os_windows    1
    #define app_os_id         windows
    #define app_os_name       "Windows"

#else

    #error "unsupported platform"

#endif

#if defined(app_os_id)

    #define app_os_path(path) app_quote(app_os_id/path)

#endif

//------------------------------------------------------------------------------

#if defined(__aarch64__)

    // ARM 64
    #define app_cpu_arm    1
    #define app_cpu_arm_64 1
    #define app_cpu_id     arm_64
    #define app_cpu_name   "ARM64"
    #define app_cpu_bits   64

#elif \
    defined(ARM)     || \
    defined(_ARM)    || \
    defined(__arm)   || \
    defined(__arm__)

    // ARM 32
    #define app_cpu_arm    1
    #define app_cpu_arm_32 1
    #define app_cpu_id     arm_32
    #define app_cpu_name   "ARM"
    #define app_cpu_bits   32

#elif \
    defined(__powerpc64__) || \
    defined(__ppc64__)

    // PPC 64
    #define app_cpu_ppc    1
    #define app_cpu_ppc_64 1
    #define app_cpu_id     ppc_64
    #define app_cpu_name   "PowerPC 64"
    #define app_cpu_bits   64

#elif \
    defined(__POWERPC__) || \
    defined(__PPC__)     || \
    defined(__powerpc__) || \
    defined(__ppc__)     || \
    defined(_POWER)      || \
    defined(powerpc)

    // PPC 32
    #define app_cpu_ppc    1
    #define app_cpu_ppc_32 1
    #define app_cpu_id     ppc_32
    #define app_cpu_name   "PowerPC"
    #define app_cpu_bits   32

#elif \
    defined(_M_X64)     || \
    defined(_M_AMD64)   || \
    defined(__x86_64__)

    // x86-64
    #define app_cpu_x86    1
    #define app_cpu_x86_64 1
    #define app_cpu_id     x86_64
    #define app_cpu_name   "x86-64"
    #define app_cpu_bits   64

#elif \
    defined(_M_IX86)  || \
    defined(__386__)  || \
    defined(__i386__) || \
    defined(__X86__)  || \
    defined(i386)

    // x86
    #define app_cpu_x86    1
    #define app_cpu_x86_32 1
    #define app_cpu_id     x86_32
    #define app_cpu_name   "x86"
    #define app_cpu_bits   32

#else

    #error "unrecognized CPU architecture"

#endif

//------------------------------------------------------------------------------

#if app_cpu_x86 || app_cpu_x86_64 || (app_cpu_arm && !__BIG_ENDIAN__)

    #define app_endian_le     0x01020304u
    #define app_endian_be     0
    #define app_endian        app_endian_le
    #define app_endian_name   "little endian"

#elif app_cpu_ppc

    #define app_endian_le     0
    #define app_endian_be     0x04030201u
    #define app_endian        app_endian_be
    #define app_endian_name   "big endian"

#else

    #error "unrecognized endianness"

#endif
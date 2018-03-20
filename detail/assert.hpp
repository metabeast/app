#pragma once
#include <ciso646>
#include <cstdio>
#include <sstream>
#include "format.hpp"

#ifndef app_assert_enabled
    #if defined(DEBUG) || defined(_DEBUG)
        #define app_assert_enabled 1
    #elif defined(__GNUC__) && !defined(__OPTIMIZE)
        #define app_assert_enabled 1
    #elif defined(assert_enabled)
        #define app_assert_enabled assert_enabled
    #endif
#endif

namespace app::assert {

    struct location {
        const char* file; int line;
        const char* function;
        const char* parameters;
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    write_to(FILE* file, const char* msg) { fputs(msg,file); }

    void
    write(const char* msg) { write_to(stdout,msg); }

    template<typename... Args>
    void
    write(Args&&... args) { write(detail::format(args...).c_str()); }

    template<typename... Args>
    void
    write(const location& loc, Args&&... args) {
        write(loc.file,":",loc.line,": ",loc.function,loc.parameters);
        write(args...);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    log(const location& loc) {
        write(loc,"\n");
    }

    template<typename... Args>
    void
    log(const location& loc, Args&&... args) {
        write(loc," ",args...,"\n");
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    err(const location& loc) {
        write(loc," error\n");
        abort();
    }

    template<typename... Args>
    void
    err(const location& loc, Args&&... args) {
        write(loc," error: ",args...,"\n");
        abort();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    todo(const location& loc) {
        write(loc," todo\n");
    }

    template<typename... Args>
    void
    todo(const location& loc, Args&&... args) {
        write(loc," todo: ",args...,"\n");
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    warn(const location& loc) {
        write(loc," warning\n");
    }

    template<typename... Args>
    void
    warn(const location& loc, Args&&... args) {
        write(loc," warning: ",args...,"\n");
    }

} // namespace app::assert

#define _app_stringify_(...) #__VA_ARGS__
#define _app_stringify(x) _app_stringify_(x)

#define _app_location {__FILE__, __LINE__, __func__,"()"}

#if app_assert_enabled

    #define app_assert(expr) ((void)( \
        bool(expr) or \
        (app_err("app_assert",_app_stringify((expr))),false) \
    ))

#else

    #define app_assert(expr) ((void)0)

#endif

#define app_log(...) ( \
    ::app::assert::log(_app_location, ##__VA_ARGS__) \
)

#define app_err(...) ( \
    ::app::assert::err(_app_location, ##__VA_ARGS__) \
)

#define app_todo(...) ( \
    ::app::assert::todo(_app_location, ##__VA_ARGS__) \
)

#define app_warn(...) ( \
    ::app::assert::warn(_app_location, ##__VA_ARGS__) \
)

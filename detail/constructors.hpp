#pragma once

#define app_default_constructors(T) \
    T() = default; \
    T(const T&) = default;

#define app_variadic_constructor(T) \
    template<typename...Args> \
    T(const Args&...args) { app_unpack(*this<<args); }

#define app_default_and_variadic_constructors(T) \
    app_default_constructors(T) \
    app_variadic_constructor(T)

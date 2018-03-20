#pragma once
#include <iostream>

void echo(const char* expr, const bool value) {
    std::cout << expr << ": " << (value?"true":"false") << '\n';
}

void echo(const char* expr, const long double value) {
    std::cout << expr << ": " << value << '\n';
}

void echo(const char* expr, const float value) {
    std::cout << expr << ": " << value << '\n';
}

void echo(const char* expr, const char value) {
    std::cout << expr << ": '" << value << "'\n";
}

void echo(const char* expr, const signed char value) {
    std::cout << expr << ": " << signed(value) << "\n";
}

void echo(const char* expr, const unsigned char value) {
    std::cout << expr << ": " << unsigned(value) << "\n";
}

void echo(const char* expr, const char* const value) {
    if (value) std::cout << expr << ": \"" << value << "\"\n";
    else       std::cout << expr << ": null\n";
}

void echo(const char* expr, const std::string& value) {
    std::cout << expr << ": \"" << value << "\"\n";
}

template <typename T>
void echo(const char* expr, const T& value) {
    if constexpr(std::is_enum_v<T>) {
        echo(expr,std::underlying_type_t<T>(value));
    } else {
        std::cout << expr << ": " << value << '\n';
    }
}

#define echo_quote_(...) #__VA_ARGS__
#define echo_quote(...) echo_quote_(__VA_ARGS__)

#define echo(...) echo(echo_quote(__VA_ARGS__),(__VA_ARGS__))

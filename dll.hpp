#pragma once
#include <cstdio>
#include <initializer_list>
#include <new>
#include "detail/platform.hpp"

//------------------------------------------------------------------------------

#if app_clang || app_gcc

    #define dllexport __attribute__((visibility("default")))

#elif app_msvc

    #define dllexport __declspec(dllexport)

#endif

//------------------------------------------------------------------------------

namespace app {

    extern "C" {

        #ifdef app_os_microsoft

            extern void* __stdcall LoadLibraryA(const char*);
            extern int   __stdcall FreeLibrary(void*);
            extern void* __stdcall GetProcAddress(void*,const char*);

        #else

            extern void* dlopen(const char*,int);
            extern int   dlclose(void*);
            extern void* dlsym(void*,const char*);

        #endif

    } // extern "C"

    //--------------------------------------------------------------------------

    struct dll final {

        using name_list = std::initializer_list<const char*>;

        struct symbol {
            void* address = nullptr;
            symbol() = default;
            symbol(decltype(nullptr)) : symbol() {}
            symbol(void* address) : address(address) {}
            explicit operator bool() const { return address != nullptr; }
            template<typename T> operator T*() const { return (T*)address; }
            symbol operator *() const { return *((void**)address); }
        };

        void* const address = nullptr;

        dll() = default;

        dll(decltype(nullptr)) : dll() {}

        dll(const char* path)
        : address(open(path)) {
            if (not address) printf("file not found: '%s'\n",path);
        }

        dll(dll&& rhs) : address(rhs.address) { new(&rhs) dll(); }

        dll& operator =(dll&& rhs) {
            if (this != &rhs) { new(this) dll(std::move(rhs)); }
            return *this;
        }

        ~dll() { if (address) { close(address); } }

        explicit operator bool() const { return address != nullptr; }

        operator void*() const { return address; }

        symbol operator ()(const char* name) const {
            return find(address,name);
        }

        symbol operator ()(name_list names) const {
            for (const char* name : names) {
                if (void* const symbol {find(address,name)}) {
                    return symbol;
                }
            }
            return nullptr;
        }

    private:

        static void* open(const char* path) {
            #if app_os_microsoft
                return LoadLibraryA(path);
            #else
                enum : int { RTLD_LAZY = 0x1, RTLD_LOCAL = 0x4 };
                return dlopen(path,RTLD_LAZY|RTLD_LOCAL);
            #endif
        }

        static void close(void* module) {
            #if app_os_microsoft
                FreeLibrary(module);
            #else
                dlclose(module);
            #endif
        }

        static void* find(void* module, const char* name) {
            #if app_os_microsoft
                return GetProcAddress(module,name);
            #else
                return dlsym(module,name);
            #endif
        }

    };

} // namespace app
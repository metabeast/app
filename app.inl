#pragma once
#include <cassert>
#include <iostream>
#include "app.hpp"
#include "detail/subsystems.hpp"

//------------------------------------------------------------------------------

namespace app {

    int main(int argc, const char* argv[]);

    //--------------------------------------------------------------------------

    void window::fillscreen() { fullscreen(true); }

    bool window::hidden() const      { return !visible(); }
    void window::hidden(bool hidden) { visible(!hidden); }
    void window::hide()              { hidden(true); }

    void window::maximize() { maximized(true); }

    void window::minimize() { minimized(true); }

    void
    window::restore() {
        if (fullscreen()) return fullscreen(false);
        if (maximized())  return maximized(false);
        if (minimized())  return minimized(false);
        if (hidden())     return hidden(false);
    }

    void window::show() { visible(true); }

    //--------------------------------------------------------------------------

    static window::delegate window__delegate__null {};

    decltype(window::delegate::null)
    window::delegate::null { &window__delegate__null };

} // namespace app

//------------------------------------------------------------------------------

std::ostream& operator <<(std::ostream& out, const app::point& p) {
    return out<<"{x:"<<p.x<<",y:"<<p.y<<'}';
}

std::ostream& operator <<(std::ostream& out, const app::size& s) {
    return out<<"{w:"<<s.w<<",h:"<<s.h<<'}';
}

std::ostream& operator <<(std::ostream& out, const app::rect& r) {
    return out<<"{x:"<<r.x<<",y:"<<r.y<<",w:"<<r.w<<",h:"<<r.h<<'}';
}

std::ostream& operator <<(std::ostream& out, const app::display& d) {
    return out
        <<'{'
        <<"boundary:"<<d.boundary<<','
        <<"viewport:"<<d.viewport
        <<'}';
}

//------------------------------------------------------------------------------

#include "dll.hpp"
#include "detail/platform.hpp"
#if app_os_ios

    #include "os/ios/app.inl"

#elif app_os_macos

    #include "os/macos/app.inl"

#elif app_os_windows

    #include "os/windows/app.inl"

#else // app_os_?

    #error "unsupported platform"

#endif // app_os_*
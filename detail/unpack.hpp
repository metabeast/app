#pragma once

namespace app {

    inline void unpack(...) {}

    #define app_unpack(expr) ::app::unpack(((expr),0)...)

} // namespace app
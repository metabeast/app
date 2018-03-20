#pragma once
#include <cstdint>

namespace app::gpu {

    enum struct color_mask {
        NONE,
        R    = 1<<0,
        G    = 1<<1,
        B    = 1<<2,
        A    = 1<<3,
        RGB  = R|G|B,
        RGBA = R|G|B|A,
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct color {
        T r {}, g {}, b {}, a {};

        color() = default;

        color(T r, T g, T b, T a = 1)
        :r{r},g{g},b{b},a{a} {}
    };

    //--------------------------------------------------------------------------

    using rgba8 = color<uint8_t>;

    using rgba32f = color<float>;

} // namespace app::gpu
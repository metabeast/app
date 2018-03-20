#pragma once

namespace app::gpu::math {

    template<typename T>
    struct vector2;

    //--------------------------------------------------------------------------

    template<typename T, unsigned I, unsigned J>
    struct swizzle2 {
        swizzle2() = delete;
        swizzle2(const swizzle2&) = delete;

        vector2<T> operator=(const vector2<T>& v) {
            static_assert(
                I != J,
                "cannot assign to swizzle with duplicate axes"
            );
            using P = T*;
            P(this)[I] = P(&v)[0];
            P(this)[J] = P(&v)[1];
            return v;
        }

        operator vector2<T>() const {
            using P = T*;
            return { P(this)[I], P(this)[J] };
        }
    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
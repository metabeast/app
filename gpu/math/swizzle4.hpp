#pragma once

namespace app::gpu::math {

    template<typename T>
    struct vector4;

    //--------------------------------------------------------------------------

    template<typename T, unsigned I, unsigned J, unsigned K, unsigned L>
    struct swizzle4 {
        swizzle4() = delete;
        swizzle4(const swizzle4&) = delete;

        vector4<T> operator=(const vector4<T>& v) {
            static_assert(
                I != J and I != K and J != K,
                "cannot assign to swizzle with duplicate axes"
            );
            using P = T*;
            P(this)[I] = P(&v)[0];
            P(this)[J] = P(&v)[1];
            P(this)[K] = P(&v)[2];
            P(this)[L] = P(&v)[3];
            return v;
        }

        operator vector4<T>() const {
            using P = T*;
            return { P(this)[I], P(this)[J], P(this)[K], P(this)[L] };
        }
    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
#pragma once

namespace app::gpu::math {

    template<typename T>
    struct vector3;

    //--------------------------------------------------------------------------

    template<typename T, unsigned I, unsigned J, unsigned K>
    struct swizzle3 {
        swizzle3() = delete;
        swizzle3(const swizzle3&) = delete;

        vector3<T> operator=(const vector3<T>& v) {
            static_assert(
                I != J and I != K and J != K,
                "cannot assign to swizzle with duplicate axes"
            );
            using P = T*;
            P(this)[I] = P(&v)[0];
            P(this)[J] = P(&v)[1];
            P(this)[K] = P(&v)[2];
            return v;
        }

        operator vector3<T>() const {
            using P = T*;
            return { P(this)[I], P(this)[J], P(this)[K] };
        }
    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
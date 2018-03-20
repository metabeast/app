#pragma once
#include "vector.hpp"

namespace app::gpu::math {

    template<typename T>
    struct matrix2x2 {
        using vector = vector<2,T>;

        vector x,y;

        matrix2x2() = default;

        explicit
        matrix2x2(T d)
        : x(d,0)
        , y(0,d) {}

        matrix2x2(
            vector x,
            vector y
        )
        : x(x)
        , y(y) {}

        matrix2x2(
            T xx, T xy,
            T yx, T yy
        )
        : x(xx,xy)
        , y(yx,yy) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct matrix2x3 {
        using vector = vector<3,T>;

        vector x,y;

        matrix2x3() = default;

        explicit
        matrix2x3(T d)
        : x(d,0,0)
        , y(0,d,0) {}

        matrix2x3(
            vector x,
            vector y
        )
        : x(x)
        , y(y) {}

        matrix2x3(
            T xx, T xy, T xz,
            T yx, T yy, T yz
        )
        : x(xx,xy,xz)
        , y(yx,yy,yz) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct matrix2x4 {
        using vector = vector<4,T>;

        vector x,y;

        matrix2x4() = default;

        explicit
        matrix2x4(T d)
        : x(d,0,0,0)
        , y(0,d,0,0) {}

        matrix2x4(
            vector x,
            vector y
        )
        : x(x)
        , y(y) {}

        matrix2x4(
            T xx, T xy, T xz, T xw,
            T yx, T yy, T yz, T yw
        )
        : x(xx,xy,xz,xw)
        , y(yx,yy,yz,yw) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
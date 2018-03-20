#pragma once
#include "vector.hpp"

namespace app::gpu::math {

    template<typename T>
    struct matrix3x2 {
        using vector = vector<2,T>;

        vector x,y,z;

        matrix3x2() = default;

        explicit
        matrix3x2(T d)
        : x(d,0)
        , y(0,d)
        , z(0,0) {}

        matrix3x2(
            vector x,
            vector y,
            vector z
        )
        : x(x)
        , y(y)
        , z(z) {}

        matrix3x2(
            T xx, T xy,
            T yx, T yy,
            T zx, T zy
        )
        : x(xx,xy)
        , y(yx,yy)
        , z(zx,zy) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct matrix3x3 {
        using vector = vector<3,T>;

        vector x,y,z;

        matrix3x3() = default;

        explicit
        matrix3x3(T d)
        : x(d,0,0)
        , y(0,d,0)
        , z(0,0,d) {}

        matrix3x3(
            vector x,
            vector y,
            vector z
        )
        : x(x)
        , y(y)
        , z(z) {}

        matrix3x3(
            T xx, T xy, T xz,
            T yx, T yy, T yz,
            T zx, T zy, T zz
        )
        : x(xx,xy,xz)
        , y(yx,yy,yz)
        , z(zx,zy,zz) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct matrix3x4 {
        using vector = vector<4,T>;

        vector x,y,z;

        matrix3x4() = default;

        explicit
        matrix3x4(T d)
        : x(d,0,0,0)
        , y(0,d,0,0)
        , z(0,0,d,0) {}

        matrix3x4(
            vector x,
            vector y,
            vector z
        )
        : x(x)
        , y(y)
        , z(z) {}

        matrix3x4(
            T xx, T xy, T xz, T xw,
            T yx, T yy, T yz, T yw,
            T zx, T zy, T zz, T zw
        )
        : x(xx,xy,xz,xw)
        , y(yx,yy,yz,yw)
        , z(zx,zy,zz,zw) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
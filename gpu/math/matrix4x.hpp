#pragma once
#include "vector.hpp"

namespace app::gpu::math {

    template<typename T>
    struct matrix4x2 {
        using vector = vector<2,T>;

        vector x,y,z,w;

        matrix4x2() = default;

        explicit
        matrix4x2(T d)
        : x(d,0)
        , y(0,d)
        , z(0,0)
        , w(0,0) {}

        matrix4x2(
            vector x,
            vector y,
            vector z,
            vector w
        )
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

        matrix4x2(
            T xx, T xy,
            T yx, T yy,
            T zx, T zy,
            T wx, T wy
        )
        : x(xx,xy)
        , y(yx,yy)
        , z(zx,zy)
        , w(wx,wy) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct matrix4x3 {
        using vector = vector<3,T>;

        vector x,y,z,w;

        matrix4x3() = default;

        explicit
        matrix4x3(T d)
        : x(d,0,0)
        , y(0,d,0)
        , z(0,0,d)
        , w(0,0,0) {}

        matrix4x3(
            vector x,
            vector y,
            vector z,
            vector w
        )
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

        matrix4x3(
            T xx, T xy, T xz,
            T yx, T yy, T yz,
            T zx, T zy, T zz,
            T wx, T wy, T wz
        )
        : x(xx,xy,xz)
        , y(yx,yy,yz)
        , z(zx,zy,zz)
        , w(wx,wy,wz) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct matrix4x4 {
        using vector = vector<4,T>;

        vector x,y,z,w;

        matrix4x4() = default;

        explicit
        matrix4x4(T d)
        : x(d,0,0,0)
        , y(0,d,0,0)
        , z(0,0,d,0)
        , w(0,0,0,d) {}

        matrix4x4(
            vector x,
            vector y,
            vector z,
            vector w
        )
        : x(x)
        , y(y)
        , z(z)
        , w(w) {}

        matrix4x4(
            T xx, T xy, T xz, T xw,
            T yx, T yy, T yz, T yw,
            T zx, T zy, T zz, T zw,
            T wx, T wy, T wz, T ww
        )
        : x(xx,xy,xz,xw)
        , y(yx,yy,yz,yw)
        , z(zx,zy,zz,zw)
        , w(wx,wy,wz,ww) {}

        vector  operator[](unsigned n) const { return (&x)[n]; }
        vector& operator[](unsigned n)       { return (&x)[n]; }
    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
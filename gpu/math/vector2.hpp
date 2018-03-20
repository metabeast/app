#pragma once
#include "swizzle2.hpp"
#include "swizzle3.hpp"
#include "swizzle4.hpp"

namespace app::gpu::math {

    template<typename T>
    struct vector2 final {
        union {
            struct { T x,y; };
            struct { T r,g; };
            struct { T s,t; };
            swizzle2<T,0,0>     xx,   rr,   ss;
            swizzle2<T,0,1>     xy,   rg,   st;
            swizzle2<T,1,0>     yx,   gr,   ts;
            swizzle2<T,1,1>     yy,   gg,   tt;
            swizzle3<T,0,0,0>   xxx,  rrr,  sss;
            swizzle3<T,0,0,1>   xxy,  rrg,  sst;
            swizzle3<T,0,1,0>   xyx,  rgr,  sts;
            swizzle3<T,0,1,1>   xyy,  rgg,  stt;
            swizzle3<T,1,0,0>   yxx,  grr,  tss;
            swizzle3<T,1,0,1>   yxy,  grg,  tst;
            swizzle3<T,1,1,0>   yyx,  ggr,  tts;
            swizzle3<T,1,1,1>   yyy,  ggg,  ttt;
            swizzle4<T,0,0,0,0> xxxx, rrrr, ssss;
            swizzle4<T,0,0,0,1> xxxy, rrrg, ssst;
            swizzle4<T,0,0,1,0> xxyx, rrgr, ssts;
            swizzle4<T,0,0,1,1> xxyy, rrgg, sstt;
            swizzle4<T,0,1,0,0> xyxx, rgrr, stss;
            swizzle4<T,0,1,0,1> xyxy, rgrg, stst;
            swizzle4<T,0,1,1,0> xyyx, rggr, stts;
            swizzle4<T,0,1,1,1> xyyy, rggg, sttt;
            swizzle4<T,1,0,0,0> yxxx, grrr, tsss;
            swizzle4<T,1,0,0,1> yxxy, grrg, tsst;
            swizzle4<T,1,0,1,0> yxyx, grgr, tsts;
            swizzle4<T,1,0,1,1> yxyy, grgg, tstt;
            swizzle4<T,1,1,0,0> yyxx, ggrr, ttss;
            swizzle4<T,1,1,0,1> yyxy, ggrg, ttst;
            swizzle4<T,1,1,1,0> yyyx, gggr, ttts;
            swizzle4<T,1,1,1,1> yyyy, gggg, tttt;
        };

        vector2()         : x( ),y( ) {}
        vector2(T u)      : x(u),y(u) {}
        vector2(T x, T y) : x(x),y(y) {}

        template<typename V>
        explicit
        vector2(vector2<V> v) : vector2(v.x,v.y) {}

        template<typename X, typename Y>
        vector2(X x, Y y) : vector2(T(x),T(y)) {}

        vector2(const vector2& v) : vector2(v.x,v.y) {}

        vector2& operator=(const vector2& v) { return *new(this)vector2(v); }

        T  operator[](unsigned i) const { return(&x)[i]; }
        T& operator[](unsigned i)       { return(&x)[i]; }

        bool operator==(const vector2& b) const { return(x==b.x)&(y==b.y); }
        bool operator!=(const vector2& b) const { return(x!=b.x)&(y!=b.y); }

    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
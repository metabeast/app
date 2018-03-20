#pragma once
#include "vector2.hpp"

namespace app::gpu::math {

    template<typename T>
    struct vector3 final {
        union {
            struct { T x,y,z; };
            struct { T r,g,b; };
            struct { T s,t,p; };
            swizzle2<T,0,0>     xx,   rr,   ss;
            swizzle2<T,0,1>     xy,   rg,   st;
            swizzle2<T,0,2>     xz,   rb,   sp;
            swizzle2<T,1,0>     yx,   gr,   ts;
            swizzle2<T,1,1>     yy,   gg,   tt;
            swizzle2<T,1,2>     yz,   gb,   tp;
            swizzle2<T,2,0>     zx,   br,   ps;
            swizzle2<T,2,1>     zy,   bg,   pt;
            swizzle2<T,2,2>     zz,   bb,   pp;
            swizzle3<T,0,0,0>   xxx,  rrr,  sss;
            swizzle3<T,0,0,1>   xxy,  rrg,  sst;
            swizzle3<T,0,0,2>   xxz,  rrb,  ssp;
            swizzle3<T,0,1,0>   xyx,  rgr,  sts;
            swizzle3<T,0,1,1>   xyy,  rgg,  stt;
            swizzle3<T,0,1,2>   xyz,  rgb,  stp;
            swizzle3<T,0,2,0>   xzx,  rbr,  sps;
            swizzle3<T,0,2,1>   xzy,  rbg,  spt;
            swizzle3<T,0,2,2>   xzz,  rbb,  spp;
            swizzle3<T,1,0,0>   yxx,  grr,  tss;
            swizzle3<T,1,0,1>   yxy,  grg,  tst;
            swizzle3<T,1,0,2>   yxz,  grb,  tsp;
            swizzle3<T,1,1,0>   yyx,  ggr,  tts;
            swizzle3<T,1,1,1>   yyy,  ggg,  ttt;
            swizzle3<T,1,1,2>   yyz,  ggb,  ttp;
            swizzle3<T,1,2,0>   yzx,  gbr,  tps;
            swizzle3<T,1,2,1>   yzy,  gbg,  tpt;
            swizzle3<T,1,2,2>   yzz,  gbb,  tpp;
            swizzle3<T,2,0,0>   zxx,  brr,  pss;
            swizzle3<T,2,0,1>   zxy,  brg,  pst;
            swizzle3<T,2,0,2>   zxz,  brb,  psp;
            swizzle3<T,2,1,0>   zyx,  bgr,  pts;
            swizzle3<T,2,1,1>   zyy,  bgg,  ptt;
            swizzle3<T,2,1,2>   zyz,  bgb,  ptp;
            swizzle3<T,2,2,0>   zzx,  bbr,  pps;
            swizzle3<T,2,2,1>   zzy,  bbg,  ppt;
            swizzle3<T,2,2,2>   zzz,  bbb,  ppp;
            swizzle4<T,0,0,0,0> xxxx, rrrr, ssss;
            swizzle4<T,0,0,0,1> xxxy, rrrg, ssst;
            swizzle4<T,0,0,0,2> xxxz, rrrb, sssp;
            swizzle4<T,0,0,1,0> xxyx, rrgr, ssts;
            swizzle4<T,0,0,1,1> xxyy, rrgg, sstt;
            swizzle4<T,0,0,1,2> xxyz, rrgb, sstp;
            swizzle4<T,0,0,2,0> xxzx, rrbr, ssps;
            swizzle4<T,0,0,2,1> xxzy, rrbg, sspt;
            swizzle4<T,0,0,2,2> xxzz, rrbb, sspp;
            swizzle4<T,0,1,0,0> xyxx, rgrr, stss;
            swizzle4<T,0,1,0,1> xyxy, rgrg, stst;
            swizzle4<T,0,1,0,2> xyxz, rgrb, stsp;
            swizzle4<T,0,1,1,0> xyyx, rggr, stts;
            swizzle4<T,0,1,1,1> xyyy, rggg, sttt;
            swizzle4<T,0,1,1,2> xyyz, rggb, sttp;
            swizzle4<T,0,1,2,0> xyzx, rgbr, stps;
            swizzle4<T,0,1,2,1> xyzy, rgbg, stpt;
            swizzle4<T,0,1,2,2> xyzz, rgbb, stpp;
            swizzle4<T,0,2,0,0> xzxx, rbrr, spss;
            swizzle4<T,0,2,0,1> xzxy, rbrg, spst;
            swizzle4<T,0,2,0,2> xzxz, rbrb, spsp;
            swizzle4<T,0,2,1,0> xzyx, rbgr, spts;
            swizzle4<T,0,2,1,1> xzyy, rbgg, sptt;
            swizzle4<T,0,2,1,2> xzyz, rbgb, sptp;
            swizzle4<T,0,2,2,0> xzzx, rbbr, spps;
            swizzle4<T,0,2,2,1> xzzy, rbbg, sppt;
            swizzle4<T,0,2,2,2> xzzz, rbbb, sppp;
            swizzle4<T,1,0,0,0> yxxx, grrr, tsss;
            swizzle4<T,1,0,0,1> yxxy, grrg, tsst;
            swizzle4<T,1,0,0,2> yxxz, grrb, tssp;
            swizzle4<T,1,0,1,0> yxyx, grgr, tsts;
            swizzle4<T,1,0,1,1> yxyy, grgg, tstt;
            swizzle4<T,1,0,1,2> yxyz, grgb, tstp;
            swizzle4<T,1,0,2,0> yxzx, grbr, tsps;
            swizzle4<T,1,0,2,1> yxzy, grbg, tspt;
            swizzle4<T,1,0,2,2> yxzz, grbb, tspp;
            swizzle4<T,1,1,0,0> yyxx, ggrr, ttss;
            swizzle4<T,1,1,0,1> yyxy, ggrg, ttst;
            swizzle4<T,1,1,0,2> yyxz, ggrb, ttsp;
            swizzle4<T,1,1,1,0> yyyx, gggr, ttts;
            swizzle4<T,1,1,1,1> yyyy, gggg, tttt;
            swizzle4<T,1,1,1,2> yyyz, gggb, tttp;
            swizzle4<T,1,1,2,0> yyzx, ggbr, ttps;
            swizzle4<T,1,1,2,1> yyzy, ggbg, ttpt;
            swizzle4<T,1,1,2,2> yyzz, ggbb, ttpp;
            swizzle4<T,1,2,0,0> yzxx, gbrr, tpss;
            swizzle4<T,1,2,0,1> yzxy, gbrg, tpst;
            swizzle4<T,1,2,0,2> yzxz, gbrb, tpsp;
            swizzle4<T,1,2,1,0> yzyx, gbgr, tpts;
            swizzle4<T,1,2,1,1> yzyy, gbgg, tptt;
            swizzle4<T,1,2,1,2> yzyz, gbgb, tptp;
            swizzle4<T,1,2,2,0> yzzx, gbbr, tpps;
            swizzle4<T,1,2,2,1> yzzy, gbbg, tppt;
            swizzle4<T,1,2,2,2> yzzz, gbbb, tppp;
            swizzle4<T,2,0,0,0> zxxx, brrr, psss;
            swizzle4<T,2,0,0,1> zxxy, brrg, psst;
            swizzle4<T,2,0,0,2> zxxz, brrb, pssp;
            swizzle4<T,2,0,1,0> zxyx, brgr, psts;
            swizzle4<T,2,0,1,1> zxyy, brgg, pstt;
            swizzle4<T,2,0,1,2> zxyz, brgb, pstp;
            swizzle4<T,2,0,2,0> zxzx, brbr, psps;
            swizzle4<T,2,0,2,1> zxzy, brbg, pspt;
            swizzle4<T,2,0,2,2> zxzz, brbb, pspp;
            swizzle4<T,2,1,0,0> zyxx, bgrr, ptss;
            swizzle4<T,2,1,0,1> zyxy, bgrg, ptst;
            swizzle4<T,2,1,0,2> zyxz, bgrb, ptsp;
            swizzle4<T,2,1,1,0> zyyx, bggr, ptts;
            swizzle4<T,2,1,1,1> zyyy, bggg, pttt;
            swizzle4<T,2,1,1,2> zyyz, bggb, pttp;
            swizzle4<T,2,1,2,0> zyzx, bgbr, ptps;
            swizzle4<T,2,1,2,1> zyzy, bgbg, ptpt;
            swizzle4<T,2,1,2,2> zyzz, bgbb, ptpp;
            swizzle4<T,2,2,0,0> zzxx, bbrr, ppss;
            swizzle4<T,2,2,0,1> zzxy, bbrg, ppst;
            swizzle4<T,2,2,0,2> zzxz, bbrb, ppsp;
            swizzle4<T,2,2,1,0> zzyx, bbgr, ppts;
            swizzle4<T,2,2,1,1> zzyy, bbgg, pptt;
            swizzle4<T,2,2,1,2> zzyz, bbgb, pptp;
            swizzle4<T,2,2,2,0> zzzx, bbbr, ppps;
            swizzle4<T,2,2,2,1> zzzy, bbbg, pppt;
            swizzle4<T,2,2,2,2> zzzz, bbbb, pppp;
        };

        vector3()              : x( ),y( ),z( ) {}
        vector3(T u)           : x(u),y(u),z(u) {}
        vector3(T x, T y)      : x(x),y(y),z( ) {}
        vector3(T x, T y, T z) : x(x),y(y),z(z) {}

        template<typename V>
        explicit
        vector3(vector3<V> v) : vector3(v.x,v.y,v.z) {}

        template<typename V, typename Z>
        vector3(vector2<V> v, Z z) : vector3(v.x,v.y,z) {}

        template<typename X, typename V>
        vector3(X x, vector2<V> v) : vector3(x,v.x,v.y) {}

        template<typename X, typename Y, typename Z>
        vector3(X x, Y y, Z z) : vector3(T(x),T(y),T(z)) {}

        vector3(const vector3& v) : vector3(v.x,v.y,v.z) {}

        vector3& operator=(const vector3& v) { return *new(this)vector3(v); }

        T  operator[](unsigned i) const { return(&x)[i]; }
        T& operator[](unsigned i)       { return(&x)[i]; }

        bool operator==(const vector3& b) const
        { return(x==b.x)&(y==b.y)&(z==b.z); }

        bool operator!=(const vector3& b) const
        { return(x!=b.x)&(y!=b.y)&(z!=b.z); }

    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
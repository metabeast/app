#pragma once
#include "vector3.hpp"

namespace app::gpu::math {

    template<typename T>
    struct vector4 final {
        union {
            struct { T x,y,z,w; };
            struct { T r,g,b,a; };
            struct { T s,t,p,q; };
            swizzle2<T,0,0>     xx,   rr,   ss;
            swizzle2<T,0,1>     xy,   rg,   st;
            swizzle2<T,0,2>     xz,   rb,   sp;
            swizzle2<T,0,3>     xw,   ra,   sq;
            swizzle2<T,1,0>     yx,   gr,   ts;
            swizzle2<T,1,1>     yy,   gg,   tt;
            swizzle2<T,1,2>     yz,   gb,   tp;
            swizzle2<T,1,3>     yw,   ga,   tq;
            swizzle2<T,2,0>     zx,   br,   ps;
            swizzle2<T,2,1>     zy,   bg,   pt;
            swizzle2<T,2,2>     zz,   bb,   pp;
            swizzle2<T,2,3>     zw,   ba,   pq;
            swizzle2<T,3,0>     wx,   ar,   qs;
            swizzle2<T,3,1>     wy,   ag,   qt;
            swizzle2<T,3,2>     wz,   ab,   qp;
            swizzle2<T,3,3>     ww,   aa,   qq;
            swizzle3<T,0,0,0>   xxx,  rrr,  sss;
            swizzle3<T,0,0,1>   xxy,  rrg,  sst;
            swizzle3<T,0,0,2>   xxz,  rrb,  ssp;
            swizzle3<T,0,0,3>   xxw,  rra,  ssq;
            swizzle3<T,0,1,0>   xyx,  rgr,  sts;
            swizzle3<T,0,1,1>   xyy,  rgg,  stt;
            swizzle3<T,0,1,2>   xyz,  rgb,  stp;
            swizzle3<T,0,1,3>   xyw,  rga,  stq;
            swizzle3<T,0,2,0>   xzx,  rbr,  sps;
            swizzle3<T,0,2,1>   xzy,  rbg,  spt;
            swizzle3<T,0,2,2>   xzz,  rbb,  spp;
            swizzle3<T,0,2,3>   xzw,  rba,  spq;
            swizzle3<T,0,3,0>   xwx,  rar,  sqs;
            swizzle3<T,0,3,1>   xwy,  rag,  sqt;
            swizzle3<T,0,3,2>   xwz,  rab,  sqp;
            swizzle3<T,0,3,3>   xww,  raa,  sqq;
            swizzle3<T,1,0,0>   yxx,  grr,  tss;
            swizzle3<T,1,0,1>   yxy,  grg,  tst;
            swizzle3<T,1,0,2>   yxz,  grb,  tsp;
            swizzle3<T,1,0,3>   yxw,  gra,  tsq;
            swizzle3<T,1,1,0>   yyx,  ggr,  tts;
            swizzle3<T,1,1,1>   yyy,  ggg,  ttt;
            swizzle3<T,1,1,2>   yyz,  ggb,  ttp;
            swizzle3<T,1,1,3>   yyw,  gga,  ttq;
            swizzle3<T,1,2,0>   yzx,  gbr,  tps;
            swizzle3<T,1,2,1>   yzy,  gbg,  tpt;
            swizzle3<T,1,2,2>   yzz,  gbb,  tpp;
            swizzle3<T,1,2,3>   yzw,  gba,  tpq;
            swizzle3<T,1,3,0>   ywx,  gar,  tqs;
            swizzle3<T,1,3,1>   ywy,  gag,  tqt;
            swizzle3<T,1,3,2>   ywz,  gab,  tqp;
            swizzle3<T,1,3,3>   yww,  gaa,  tqq;
            swizzle3<T,2,0,0>   zxx,  brr,  pss;
            swizzle3<T,2,0,1>   zxy,  brg,  pst;
            swizzle3<T,2,0,2>   zxz,  brb,  psp;
            swizzle3<T,2,0,3>   zxw,  bra,  psq;
            swizzle3<T,2,1,0>   zyx,  bgr,  pts;
            swizzle3<T,2,1,1>   zyy,  bgg,  ptt;
            swizzle3<T,2,1,2>   zyz,  bgb,  ptp;
            swizzle3<T,2,1,3>   zyw,  bga,  ptq;
            swizzle3<T,2,2,0>   zzx,  bbr,  pps;
            swizzle3<T,2,2,1>   zzy,  bbg,  ppt;
            swizzle3<T,2,2,2>   zzz,  bbb,  ppp;
            swizzle3<T,2,2,3>   zzw,  bba,  ppq;
            swizzle3<T,2,3,0>   zwx,  bar,  pqs;
            swizzle3<T,2,3,1>   zwy,  bag,  pqt;
            swizzle3<T,2,3,2>   zwz,  bab,  pqp;
            swizzle3<T,2,3,3>   zww,  baa,  pqq;
            swizzle3<T,3,0,0>   wxx,  arr,  qss;
            swizzle3<T,3,0,1>   wxy,  arg,  qst;
            swizzle3<T,3,0,2>   wxz,  arb,  qsp;
            swizzle3<T,3,0,3>   wxw,  ara,  qsq;
            swizzle3<T,3,1,0>   wyx,  agr,  qts;
            swizzle3<T,3,1,1>   wyy,  agg,  qtt;
            swizzle3<T,3,1,2>   wyz,  agb,  qtp;
            swizzle3<T,3,1,3>   wyw,  aga,  qtq;
            swizzle3<T,3,2,0>   wzx,  abr,  qps;
            swizzle3<T,3,2,1>   wzy,  abg,  qpt;
            swizzle3<T,3,2,2>   wzz,  abb,  qpp;
            swizzle3<T,3,2,3>   wzw,  aba,  qpq;
            swizzle3<T,3,3,0>   wwx,  aar,  qqs;
            swizzle3<T,3,3,1>   wwy,  aag,  qqt;
            swizzle3<T,3,3,2>   wwz,  aab,  qqp;
            swizzle3<T,3,3,3>   www,  aaa,  qqq;
            swizzle4<T,0,0,0,0> xxxx, rrrr, ssss;
            swizzle4<T,0,0,0,1> xxxy, rrrg, ssst;
            swizzle4<T,0,0,0,2> xxxz, rrrb, sssp;
            swizzle4<T,0,0,0,3> xxxw, rrra, sssq;
            swizzle4<T,0,0,1,0> xxyx, rrgr, ssts;
            swizzle4<T,0,0,1,1> xxyy, rrgg, sstt;
            swizzle4<T,0,0,1,2> xxyz, rrgb, sstp;
            swizzle4<T,0,0,1,3> xxyw, rrga, sstq;
            swizzle4<T,0,0,2,0> xxzx, rrbr, ssps;
            swizzle4<T,0,0,2,1> xxzy, rrbg, sspt;
            swizzle4<T,0,0,2,2> xxzz, rrbb, sspp;
            swizzle4<T,0,0,2,3> xxzw, rrba, sspq;
            swizzle4<T,0,0,3,0> xxwx, rrar, ssqs;
            swizzle4<T,0,0,3,1> xxwy, rrag, ssqt;
            swizzle4<T,0,0,3,2> xxwz, rrab, ssqp;
            swizzle4<T,0,0,3,3> xxww, rraa, ssqq;
            swizzle4<T,0,1,0,0> xyxx, rgrr, stss;
            swizzle4<T,0,1,0,1> xyxy, rgrg, stst;
            swizzle4<T,0,1,0,2> xyxz, rgrb, stsp;
            swizzle4<T,0,1,0,3> xyxw, rgra, stsq;
            swizzle4<T,0,1,1,0> xyyx, rggr, stts;
            swizzle4<T,0,1,1,1> xyyy, rggg, sttt;
            swizzle4<T,0,1,1,2> xyyz, rggb, sttp;
            swizzle4<T,0,1,1,3> xyyw, rgga, sttq;
            swizzle4<T,0,1,2,0> xyzx, rgbr, stps;
            swizzle4<T,0,1,2,1> xyzy, rgbg, stpt;
            swizzle4<T,0,1,2,2> xyzz, rgbb, stpp;
            swizzle4<T,0,1,2,3> xyzw, rgba, stpq;
            swizzle4<T,0,1,3,0> xywx, rgar, stqs;
            swizzle4<T,0,1,3,1> xywy, rgag, stqt;
            swizzle4<T,0,1,3,2> xywz, rgab, stqp;
            swizzle4<T,0,1,3,3> xyww, rgaa, stqq;
            swizzle4<T,0,2,0,0> xzxx, rbrr, spss;
            swizzle4<T,0,2,0,1> xzxy, rbrg, spst;
            swizzle4<T,0,2,0,2> xzxz, rbrb, spsp;
            swizzle4<T,0,2,0,3> xzxw, rbra, spsq;
            swizzle4<T,0,2,1,0> xzyx, rbgr, spts;
            swizzle4<T,0,2,1,1> xzyy, rbgg, sptt;
            swizzle4<T,0,2,1,2> xzyz, rbgb, sptp;
            swizzle4<T,0,2,1,3> xzyw, rbga, sptq;
            swizzle4<T,0,2,2,0> xzzx, rbbr, spps;
            swizzle4<T,0,2,2,1> xzzy, rbbg, sppt;
            swizzle4<T,0,2,2,2> xzzz, rbbb, sppp;
            swizzle4<T,0,2,2,3> xzzw, rbba, sppq;
            swizzle4<T,0,2,3,0> xzwx, rbar, spqs;
            swizzle4<T,0,2,3,1> xzwy, rbag, spqt;
            swizzle4<T,0,2,3,2> xzwz, rbab, spqp;
            swizzle4<T,0,2,3,3> xzww, rbaa, spqq;
            swizzle4<T,0,3,0,0> xwxx, rarr, sqss;
            swizzle4<T,0,3,0,1> xwxy, rarg, sqst;
            swizzle4<T,0,3,0,2> xwxz, rarb, sqsp;
            swizzle4<T,0,3,0,3> xwxw, rara, sqsq;
            swizzle4<T,0,3,1,0> xwyx, ragr, sqts;
            swizzle4<T,0,3,1,1> xwyy, ragg, sqtt;
            swizzle4<T,0,3,1,2> xwyz, ragb, sqtp;
            swizzle4<T,0,3,1,3> xwyw, raga, sqtq;
            swizzle4<T,0,3,2,0> xwzx, rabr, sqps;
            swizzle4<T,0,3,2,1> xwzy, rabg, sqpt;
            swizzle4<T,0,3,2,2> xwzz, rabb, sqpp;
            swizzle4<T,0,3,2,3> xwzw, raba, sqpq;
            swizzle4<T,0,3,3,0> xwwx, raar, sqqs;
            swizzle4<T,0,3,3,1> xwwy, raag, sqqt;
            swizzle4<T,0,3,3,2> xwwz, raab, sqqp;
            swizzle4<T,0,3,3,3> xwww, raaa, sqqq;
            swizzle4<T,1,0,0,0> yxxx, grrr, tsss;
            swizzle4<T,1,0,0,1> yxxy, grrg, tsst;
            swizzle4<T,1,0,0,2> yxxz, grrb, tssp;
            swizzle4<T,1,0,0,3> yxxw, grra, tssq;
            swizzle4<T,1,0,1,0> yxyx, grgr, tsts;
            swizzle4<T,1,0,1,1> yxyy, grgg, tstt;
            swizzle4<T,1,0,1,2> yxyz, grgb, tstp;
            swizzle4<T,1,0,1,3> yxyw, grga, tstq;
            swizzle4<T,1,0,2,0> yxzx, grbr, tsps;
            swizzle4<T,1,0,2,1> yxzy, grbg, tspt;
            swizzle4<T,1,0,2,2> yxzz, grbb, tspp;
            swizzle4<T,1,0,2,3> yxzw, grba, tspq;
            swizzle4<T,1,0,3,0> yxwx, grar, tsqs;
            swizzle4<T,1,0,3,1> yxwy, grag, tsqt;
            swizzle4<T,1,0,3,2> yxwz, grab, tsqp;
            swizzle4<T,1,0,3,3> yxww, graa, tsqq;
            swizzle4<T,1,1,0,0> yyxx, ggrr, ttss;
            swizzle4<T,1,1,0,1> yyxy, ggrg, ttst;
            swizzle4<T,1,1,0,2> yyxz, ggrb, ttsp;
            swizzle4<T,1,1,0,3> yyxw, ggra, ttsq;
            swizzle4<T,1,1,1,0> yyyx, gggr, ttts;
            swizzle4<T,1,1,1,1> yyyy, gggg, tttt;
            swizzle4<T,1,1,1,2> yyyz, gggb, tttp;
            swizzle4<T,1,1,1,3> yyyw, ggga, tttq;
            swizzle4<T,1,1,2,0> yyzx, ggbr, ttps;
            swizzle4<T,1,1,2,1> yyzy, ggbg, ttpt;
            swizzle4<T,1,1,2,2> yyzz, ggbb, ttpp;
            swizzle4<T,1,1,2,3> yyzw, ggba, ttpq;
            swizzle4<T,1,1,3,0> yywx, ggar, ttqs;
            swizzle4<T,1,1,3,1> yywy, ggag, ttqt;
            swizzle4<T,1,1,3,2> yywz, ggab, ttqp;
            swizzle4<T,1,1,3,3> yyww, ggaa, ttqq;
            swizzle4<T,1,2,0,0> yzxx, gbrr, tpss;
            swizzle4<T,1,2,0,1> yzxy, gbrg, tpst;
            swizzle4<T,1,2,0,2> yzxz, gbrb, tpsp;
            swizzle4<T,1,2,0,3> yzxw, gbra, tpsq;
            swizzle4<T,1,2,1,0> yzyx, gbgr, tpts;
            swizzle4<T,1,2,1,1> yzyy, gbgg, tptt;
            swizzle4<T,1,2,1,2> yzyz, gbgb, tptp;
            swizzle4<T,1,2,1,3> yzyw, gbga, tptq;
            swizzle4<T,1,2,2,0> yzzx, gbbr, tpps;
            swizzle4<T,1,2,2,1> yzzy, gbbg, tppt;
            swizzle4<T,1,2,2,2> yzzz, gbbb, tppp;
            swizzle4<T,1,2,2,3> yzzw, gbba, tppq;
            swizzle4<T,1,2,3,0> yzwx, gbar, tpqs;
            swizzle4<T,1,2,3,1> yzwy, gbag, tpqt;
            swizzle4<T,1,2,3,2> yzwz, gbab, tpqp;
            swizzle4<T,1,2,3,3> yzww, gbaa, tpqq;
            swizzle4<T,1,3,0,0> ywxx, garr, tqss;
            swizzle4<T,1,3,0,1> ywxy, garg, tqst;
            swizzle4<T,1,3,0,2> ywxz, garb, tqsp;
            swizzle4<T,1,3,0,3> ywxw, gara, tqsq;
            swizzle4<T,1,3,1,0> ywyx, gagr, tqts;
            swizzle4<T,1,3,1,1> ywyy, gagg, tqtt;
            swizzle4<T,1,3,1,2> ywyz, gagb, tqtp;
            swizzle4<T,1,3,1,3> ywyw, gaga, tqtq;
            swizzle4<T,1,3,2,0> ywzx, gabr, tqps;
            swizzle4<T,1,3,2,1> ywzy, gabg, tqpt;
            swizzle4<T,1,3,2,2> ywzz, gabb, tqpp;
            swizzle4<T,1,3,2,3> ywzw, gaba, tqpq;
            swizzle4<T,1,3,3,0> ywwx, gaar, tqqs;
            swizzle4<T,1,3,3,1> ywwy, gaag, tqqt;
            swizzle4<T,1,3,3,2> ywwz, gaab, tqqp;
            swizzle4<T,1,3,3,3> ywww, gaaa, tqqq;
            swizzle4<T,2,0,0,0> zxxx, brrr, psss;
            swizzle4<T,2,0,0,1> zxxy, brrg, psst;
            swizzle4<T,2,0,0,2> zxxz, brrb, pssp;
            swizzle4<T,2,0,0,3> zxxw, brra, pssq;
            swizzle4<T,2,0,1,0> zxyx, brgr, psts;
            swizzle4<T,2,0,1,1> zxyy, brgg, pstt;
            swizzle4<T,2,0,1,2> zxyz, brgb, pstp;
            swizzle4<T,2,0,1,3> zxyw, brga, pstq;
            swizzle4<T,2,0,2,0> zxzx, brbr, psps;
            swizzle4<T,2,0,2,1> zxzy, brbg, pspt;
            swizzle4<T,2,0,2,2> zxzz, brbb, pspp;
            swizzle4<T,2,0,2,3> zxzw, brba, pspq;
            swizzle4<T,2,0,3,0> zxwx, brar, psqs;
            swizzle4<T,2,0,3,1> zxwy, brag, psqt;
            swizzle4<T,2,0,3,2> zxwz, brab, psqp;
            swizzle4<T,2,0,3,3> zxww, braa, psqq;
            swizzle4<T,2,1,0,0> zyxx, bgrr, ptss;
            swizzle4<T,2,1,0,1> zyxy, bgrg, ptst;
            swizzle4<T,2,1,0,2> zyxz, bgrb, ptsp;
            swizzle4<T,2,1,0,3> zyxw, bgra, ptsq;
            swizzle4<T,2,1,1,0> zyyx, bggr, ptts;
            swizzle4<T,2,1,1,1> zyyy, bggg, pttt;
            swizzle4<T,2,1,1,2> zyyz, bggb, pttp;
            swizzle4<T,2,1,1,3> zyyw, bgga, pttq;
            swizzle4<T,2,1,2,0> zyzx, bgbr, ptps;
            swizzle4<T,2,1,2,1> zyzy, bgbg, ptpt;
            swizzle4<T,2,1,2,2> zyzz, bgbb, ptpp;
            swizzle4<T,2,1,2,3> zyzw, bgba, ptpq;
            swizzle4<T,2,1,3,0> zywx, bgar, ptqs;
            swizzle4<T,2,1,3,1> zywy, bgag, ptqt;
            swizzle4<T,2,1,3,2> zywz, bgab, ptqp;
            swizzle4<T,2,1,3,3> zyww, bgaa, ptqq;
            swizzle4<T,2,2,0,0> zzxx, bbrr, ppss;
            swizzle4<T,2,2,0,1> zzxy, bbrg, ppst;
            swizzle4<T,2,2,0,2> zzxz, bbrb, ppsp;
            swizzle4<T,2,2,0,3> zzxw, bbra, ppsq;
            swizzle4<T,2,2,1,0> zzyx, bbgr, ppts;
            swizzle4<T,2,2,1,1> zzyy, bbgg, pptt;
            swizzle4<T,2,2,1,2> zzyz, bbgb, pptp;
            swizzle4<T,2,2,1,3> zzyw, bbga, pptq;
            swizzle4<T,2,2,2,0> zzzx, bbbr, ppps;
            swizzle4<T,2,2,2,1> zzzy, bbbg, pppt;
            swizzle4<T,2,2,2,2> zzzz, bbbb, pppp;
            swizzle4<T,2,2,2,3> zzzw, bbba, pppq;
            swizzle4<T,2,2,3,0> zzwx, bbar, ppqs;
            swizzle4<T,2,2,3,1> zzwy, bbag, ppqt;
            swizzle4<T,2,2,3,2> zzwz, bbab, ppqp;
            swizzle4<T,2,2,3,3> zzww, bbaa, ppqq;
            swizzle4<T,2,3,0,0> zwxx, barr, pqss;
            swizzle4<T,2,3,0,1> zwxy, barg, pqst;
            swizzle4<T,2,3,0,2> zwxz, barb, pqsp;
            swizzle4<T,2,3,0,3> zwxw, bara, pqsq;
            swizzle4<T,2,3,1,0> zwyx, bagr, pqts;
            swizzle4<T,2,3,1,1> zwyy, bagg, pqtt;
            swizzle4<T,2,3,1,2> zwyz, bagb, pqtp;
            swizzle4<T,2,3,1,3> zwyw, baga, pqtq;
            swizzle4<T,2,3,2,0> zwzx, babr, pqps;
            swizzle4<T,2,3,2,1> zwzy, babg, pqpt;
            swizzle4<T,2,3,2,2> zwzz, babb, pqpp;
            swizzle4<T,2,3,2,3> zwzw, baba, pqpq;
            swizzle4<T,2,3,3,0> zwwx, baar, pqqs;
            swizzle4<T,2,3,3,1> zwwy, baag, pqqt;
            swizzle4<T,2,3,3,2> zwwz, baab, pqqp;
            swizzle4<T,2,3,3,3> zwww, baaa, pqqq;
            swizzle4<T,3,0,0,0> wxxx, arrr, qsss;
            swizzle4<T,3,0,0,1> wxxy, arrg, qsst;
            swizzle4<T,3,0,0,2> wxxz, arrb, qssp;
            swizzle4<T,3,0,0,3> wxxw, arra, qssq;
            swizzle4<T,3,0,1,0> wxyx, argr, qsts;
            swizzle4<T,3,0,1,1> wxyy, argg, qstt;
            swizzle4<T,3,0,1,2> wxyz, argb, qstp;
            swizzle4<T,3,0,1,3> wxyw, arga, qstq;
            swizzle4<T,3,0,2,0> wxzx, arbr, qsps;
            swizzle4<T,3,0,2,1> wxzy, arbg, qspt;
            swizzle4<T,3,0,2,2> wxzz, arbb, qspp;
            swizzle4<T,3,0,2,3> wxzw, arba, qspq;
            swizzle4<T,3,0,3,0> wxwx, arar, qsqs;
            swizzle4<T,3,0,3,1> wxwy, arag, qsqt;
            swizzle4<T,3,0,3,2> wxwz, arab, qsqp;
            swizzle4<T,3,0,3,3> wxww, araa, qsqq;
            swizzle4<T,3,1,0,0> wyxx, agrr, qtss;
            swizzle4<T,3,1,0,1> wyxy, agrg, qtst;
            swizzle4<T,3,1,0,2> wyxz, agrb, qtsp;
            swizzle4<T,3,1,0,3> wyxw, agra, qtsq;
            swizzle4<T,3,1,1,0> wyyx, aggr, qtts;
            swizzle4<T,3,1,1,1> wyyy, aggg, qttt;
            swizzle4<T,3,1,1,2> wyyz, aggb, qttp;
            swizzle4<T,3,1,1,3> wyyw, agga, qttq;
            swizzle4<T,3,1,2,0> wyzx, agbr, qtps;
            swizzle4<T,3,1,2,1> wyzy, agbg, qtpt;
            swizzle4<T,3,1,2,2> wyzz, agbb, qtpp;
            swizzle4<T,3,1,2,3> wyzw, agba, qtpq;
            swizzle4<T,3,1,3,0> wywx, agar, qtqs;
            swizzle4<T,3,1,3,1> wywy, agag, qtqt;
            swizzle4<T,3,1,3,2> wywz, agab, qtqp;
            swizzle4<T,3,1,3,3> wyww, agaa, qtqq;
            swizzle4<T,3,2,0,0> wzxx, abrr, qpss;
            swizzle4<T,3,2,0,1> wzxy, abrg, qpst;
            swizzle4<T,3,2,0,2> wzxz, abrb, qpsp;
            swizzle4<T,3,2,0,3> wzxw, abra, qpsq;
            swizzle4<T,3,2,1,0> wzyx, abgr, qpts;
            swizzle4<T,3,2,1,1> wzyy, abgg, qptt;
            swizzle4<T,3,2,1,2> wzyz, abgb, qptp;
            swizzle4<T,3,2,1,3> wzyw, abga, qptq;
            swizzle4<T,3,2,2,0> wzzx, abbr, qpps;
            swizzle4<T,3,2,2,1> wzzy, abbg, qppt;
            swizzle4<T,3,2,2,2> wzzz, abbb, qppp;
            swizzle4<T,3,2,2,3> wzzw, abba, qppq;
            swizzle4<T,3,2,3,0> wzwx, abar, qpqs;
            swizzle4<T,3,2,3,1> wzwy, abag, qpqt;
            swizzle4<T,3,2,3,2> wzwz, abab, qpqp;
            swizzle4<T,3,2,3,3> wzww, abaa, qpqq;
            swizzle4<T,3,3,0,0> wwxx, aarr, qqss;
            swizzle4<T,3,3,0,1> wwxy, aarg, qqst;
            swizzle4<T,3,3,0,2> wwxz, aarb, qqsp;
            swizzle4<T,3,3,0,3> wwxw, aara, qqsq;
            swizzle4<T,3,3,1,0> wwyx, aagr, qqts;
            swizzle4<T,3,3,1,1> wwyy, aagg, qqtt;
            swizzle4<T,3,3,1,2> wwyz, aagb, qqtp;
            swizzle4<T,3,3,1,3> wwyw, aaga, qqtq;
            swizzle4<T,3,3,2,0> wwzx, aabr, qqps;
            swizzle4<T,3,3,2,1> wwzy, aabg, qqpt;
            swizzle4<T,3,3,2,2> wwzz, aabb, qqpp;
            swizzle4<T,3,3,2,3> wwzw, aaba, qqpq;
            swizzle4<T,3,3,3,0> wwwx, aaar, qqqs;
            swizzle4<T,3,3,3,1> wwwy, aaag, qqqt;
            swizzle4<T,3,3,3,2> wwwz, aaab, qqqp;
            swizzle4<T,3,3,3,3> wwww, aaaa, qqqq;
        };

        vector4()                   : x( ),y( ),z( ),w( ) {}
        vector4(T u)                : x(u),y(u),z(u),w(u) {}
        vector4(T x, T y)           : x(x),y(y),z( ),w( ) {}
        vector4(T x, T y, T z)      : x(x),y(y),z(z),w( ) {}
        vector4(T x, T y, T z, T w) : x(x),y(y),z(z),w(w) {}

        template<typename V>
        explicit
        vector4(vector4<V> v) : vector4(v.x,v.y,v.z,v.w) {}

        template<typename V, typename W>
        vector4(vector3<V> v, W w) : vector4(v.x,v.y,v.z,w) {}

        template<typename X, typename V>
        vector4(X x, vector3<V> v) : vector4(x,v.x,v.y,v.z) {}

        template<typename V, typename U>
        vector4(vector2<V> v, vector2<U> u) : vector4(v.x,v.y,u.x,u.y) {}

        template<typename V, typename Z, typename W>
        vector4(vector2<V> v, Z z, W w) : vector4(v.x,v.y,z,w) {}

        template<typename X, typename V, typename W>
        vector4(X x, vector2<V> v, W w) : vector4(x,v.x,v.y,w) {}

        template<typename X, typename Y, typename V>
        vector4(X x, Y y, vector2<V> v) : vector4(x,y,v.x,v.y) {}

        template<typename X, typename Y, typename Z, typename W>
        vector4(X x, Y y, Z z, W w) : vector4(T(x),T(y),T(z),T(w)) {}

        vector4(const vector4& v) : vector4(v.x,v.y,v.z,v.w) {}

        vector4& operator=(const vector4& v) { return *new(this)vector4(v); }

        T  operator[](unsigned i) const { return(&x)[i]; }
        T& operator[](unsigned i)       { return(&x)[i]; }

        bool operator==(const vector4& b) const
        { return(x==b.x)&(y==b.y)&(z==b.z)&(w==b.w); }

        bool operator!=(const vector4& b) const
        { return(x!=b.x)&(y!=b.y)&(z!=b.z)&(w!=b.w); }

    };

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
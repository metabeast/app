#pragma once
#include <cmath>
#include <cfloat>
#include <new>
#include "int.hpp"

namespace app::gpu::math {

    class half {

        struct conversion;

        const ushort bits;

    public:

        half(float value) : bits(encode(value)) {}

        half(const half&) = default;

        half& operator=(const half& rhs) { return *new(this)half(rhs); }

        operator float() const { return decode(bits); }

        static float decode(ushort u);

        static ushort encode(float f);

    };

} // gpu::math

namespace app::gpu { using namespace app::gpu::math; }

//------------------------------------------------------------------------------
// gpu::math::half::conversion is based on:
//
// Branch-free implementation of half-precision (16 bit) floating point
// Copyright 2006 Mike Acton <macton@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a 
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included 
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE

struct app::gpu::math::half::conversion {

    using f32 = float;
    using i32 = int;
    using u16 = ushort;
    using u32 = uint;
    using U16 = const u16;
    using U32 = const u32;

    static inline float decode(ushort u) {
        enum : u32 {
            h_e_mask             = 0x00007c00u,
            h_m_mask             = 0x000003ffu,
            h_s_mask             = 0x00008000u,
            h_f_s_pos_offset     = 0x00000010u,
            h_f_e_pos_offset     = 0x0000000du,
            h_f_bias_offset      = 0x0001c000u,
            f_e_mask             = 0x7f800000u,
            f_m_mask             = 0x007fffffu,
            h_f_e_denorm_bias    = 0x0000007eu,
            h_f_m_denorm_sa_bias = 0x00000008u,
            f_e_pos              = 0x00000017u,
            h_e_mask_minus_one   = 0x00007bffu,
        };
        U32 h_e                 {uand(u,h_e_mask)};
        U32 h_m                 {uand(u,h_m_mask)};
        U32 h_s                 {uand(u,h_s_mask)};
        U32 h_e_f_bias          {uadd(h_e,h_f_bias_offset)};
        U32 h_m_nlz             {uclz(h_m)};
        U32 f_s                 {usll(h_s,h_f_s_pos_offset)};
        U32 f_e                 {usll(h_e_f_bias,h_f_e_pos_offset)};
        U32 f_m                 {usll(h_m,h_f_e_pos_offset)};
        U32 f_em                {uor(f_e,f_m)};
        U32 h_f_m_sa            {usub(h_m_nlz,h_f_m_denorm_sa_bias)};
        U32 f_e_denorm_unpacked {usub(h_f_e_denorm_bias,h_f_m_sa)};
        U32 h_f_m               {usll(h_m,h_f_m_sa)};
        U32 f_m_denorm          {uand(h_f_m,f_m_mask)};
        U32 f_e_denorm          {usll(f_e_denorm_unpacked,f_e_pos)};
        U32 f_em_denorm         {uor(f_e_denorm,f_m_denorm)};
        U32 f_em_nan            {uor(f_e_mask,f_m)};
        U32 is_e_eqz_msb        {udec(h_e)};
        U32 is_m_nez_msb        {uneg(h_m)};
        U32 is_e_flagged_msb    {usub(h_e_mask_minus_one,h_e)};
        U32 is_zero_msb         {uandc(is_e_eqz_msb,is_m_nez_msb)};
        U32 is_inf_msb          {uandc(is_e_flagged_msb,is_m_nez_msb)};
        U32 is_denorm_msb       {uand(is_m_nez_msb,is_e_eqz_msb)};
        U32 is_nan_msb          {uand(is_e_flagged_msb,is_m_nez_msb)};
        U32 is_zero             {uext(is_zero_msb)};
        U32 f_zero_result       {uandc(f_em,is_zero)};
        U32 f_denorm_result     {usels(is_denorm_msb,f_em_denorm,f_zero_result)};
        U32 f_inf_result        {usels(is_inf_msb,f_e_mask,f_denorm_result)};
        U32 f_nan_result        {usels(is_nan_msb,f_em_nan,f_inf_result)};
        U32 f_result            {uor(f_s,f_nan_result)};
        return f32(reinterpret(f_result));
    }

    static inline ushort encode(float f) {
        enum : u32 {
            one               = 0x00000001u,
            f_s_mask          = 0x80000000u,
            f_e_mask          = 0x7f800000u,
            f_m_mask          = 0x007fffffu,
            f_m_hidden_bit    = 0x00800000u,
            f_m_round_bit     = 0x00001000u,
            f_snan_mask       = 0x7fc00000u,
            f_e_pos           = 0x00000017u,
            h_e_pos           = 0x0000000au,
            h_e_mask          = 0x00007c00u,
            h_snan_mask       = 0x00007e00u,
            h_e_mask_value    = 0x0000001fu,
            f_h_s_pos_offset  = 0x00000010u,
            f_h_bias_offset   = 0x00000070u,
            f_h_m_pos_offset  = 0x0000000du,
            h_nan_min         = 0x00007c01u,
            f_h_e_biased_flag = 0x0000008fu,
        };
        U32 u                         {u32(reinterpret(f))};
        U32 f_s                       {uand(u,f_s_mask)};
        U32 f_e                       {uand(u,f_e_mask)};
        U16 h_s                       {u16(usrl(f_s,f_h_s_pos_offset))};
        U32 f_m                       {uand(u,f_m_mask)};
        U16 f_e_amount                {u16(usrl(f_e,f_e_pos))};
        U32 f_e_half_bias             {usub(f_e_amount,f_h_bias_offset)};
        U32 f_snan                    {uand(u,f_snan_mask)};
        U32 f_m_round_mask            {uand(f_m,f_m_round_bit)};
        U32 f_m_round_offset          {usll(f_m_round_mask,one)};
        U32 f_m_rounded               {uadd(f_m,f_m_round_offset)};
        U32 f_m_denorm_sa             {usub(one,f_e_half_bias)};
        U32 f_m_with_hidden           {uor(f_m_rounded,f_m_hidden_bit)};
        U32 f_m_denorm                {usrl(f_m_with_hidden,f_m_denorm_sa)};
        U32 h_m_denorm                {usrl(f_m_denorm,f_h_m_pos_offset)};
        U32 f_m_rounded_overflow      {uand(f_m_rounded,f_m_hidden_bit)};
        U32 m_nan                     {usrl(f_m,f_h_m_pos_offset)};
        U32 h_em_nan                  {uor(h_e_mask,m_nan)};
        U32 h_e_norm_overflow_offset  {uinc(f_e_half_bias)};
        U32 h_e_norm_overflow         {usll(h_e_norm_overflow_offset,h_e_pos)};
        U32 h_e_norm                  {usll(f_e_half_bias,h_e_pos)};
        U32 h_m_norm                  {usrl(f_m_rounded,f_h_m_pos_offset)};
        U32 h_em_norm                 {uor(h_e_norm,h_m_norm)};
        U32 is_h_ndenorm_msb          {usub(f_h_bias_offset,f_e_amount)};
        U32 is_f_e_flagged_msb        {usub(f_h_e_biased_flag,f_e_half_bias)};
        U32 is_h_denorm_msb           {unot(is_h_ndenorm_msb)};
        U32 is_f_m_eqz_msb            {udec(f_m)};
        U32 is_h_nan_eqz_msb          {udec(m_nan)};
        U32 is_f_inf_msb              {uand(is_f_e_flagged_msb,is_f_m_eqz_msb)};
        U32 is_f_nan_underflow_msb    {uand(is_f_e_flagged_msb,is_h_nan_eqz_msb)};
        U32 is_e_overflow_msb         {usub(h_e_mask_value,f_e_half_bias)};
        U32 is_h_inf_msb              {uor(is_e_overflow_msb,is_f_inf_msb)};
        U32 is_f_nsnan_msb            {usub(f_snan,f_snan_mask)};
        U32 is_m_norm_overflow_msb    {uneg(f_m_rounded_overflow)};
        U32 is_f_snan_msb             {unot(is_f_nsnan_msb)};
        U32 h_em_overflow_result      {usels(is_m_norm_overflow_msb,h_e_norm_overflow,h_em_norm)};
        U32 h_em_nan_result           {usels(is_f_e_flagged_msb,h_em_nan,h_em_overflow_result)};
        U32 h_em_nan_underflow_result {usels(is_f_nan_underflow_msb,h_nan_min,h_em_nan_result)};
        U32 h_em_inf_result           {usels(is_h_inf_msb,h_e_mask,h_em_nan_underflow_result)};
        U32 h_em_denorm_result        {usels(is_h_denorm_msb,h_m_denorm,h_em_inf_result)};
        U32 h_em_snan_result          {usels(is_f_snan_msb,h_snan_mask,h_em_denorm_result)};
        U32 h_result                  {uor(h_s,h_em_snan_result)};
        return u16(h_result);
    }

    union reinterpret {
        f32 f;
        u32 u;

        reinterpret(f32 f) : f(f) {}
        reinterpret(u32 u) : u(u) {}

        operator f32() const { return f; }
        operator u32() const { return u; }
    };

    static inline u32 uadd(u32 a, u32 b)  { return (a+b); }
    static inline u32 uand(u32 a, u32 b)  { return (a&b); }
    static inline u32 uandc(u32 a, u32 b) { return (a&~b); }
    static inline u32 udec(u32 a)         { return (a-1u); }
    static inline u32 udiv(u32 a, u32 b)  { return (a/b); }
    static inline u32 uext(u32 a)         { return (i32(a)>>31); }
    static inline u32 uinc(u32 a)         { return (a+1u); }
    static inline u32 umod(u32 a, u32 b)  { return (a%b); }
    static inline u32 umul(u32 a, u32 b)  { return (a*b); }
    static inline u32 uneg(u32 a)         { return (-i32(a)); }
    static inline u32 unot(u32 a)         { return (~a); }
    static inline u32 uor(u32 a, u32 b)   { return (a|b); }
    static inline u32 uorc(u32 a, u32 b)  { return (a|~b); }
    static inline u32 urol(u32 a, i32 b)  { return (a<<b)|(a>>(32-b)); }
    static inline u32 uror(u32 a, i32 b)  { return (a>>b)|(a<<(32-b)); }
    static inline u32 usll(u32 a, i32 b)  { return (a<<b); }
    static inline u32 usra(u32 a, i32 b)  { return (i32(a)>>b); }
    static inline u32 usrl(u32 a, i32 b)  { return (a>>b); }
    static inline u32 usub(u32 a, u32 b)  { return (a-b); }
    static inline u32 uxor(u32 a, u32 b)  { return (a^b); }
    static inline u32 uxorl(u32 a, u32 b) { return (!a!=!b); }

    static inline u32 usels(u32 test, u32 a, u32 b) {
        U32 mask  = uext(test);
        U32 sel_a = uand(a,mask);
        U32 sel_b = uandc(b,mask);
        return uor(sel_a,sel_b);
    }

    static inline u32 uclz(u32 a) {
        U32 b {usrl(a,1u)};
        U32 c {uor(a,b)};
        U32 d {usrl(c,2u)};
        U32 e {uor(c,d)};
        U32 f {usrl(e,4u)};
        U32 g {uor(e,f)};
        U32 h {usrl(g,8u)};
        U32 i {uor(g,h)};
        U32 j {usrl(i,16u)};
        U32 k {uor(i,j)};
        U32 l {unot(k)};
        U32 m {usrl(l,1u)};
        U32 n {uand(m,0x55555555u)};
        U32 o {usub(l,n)};
        U32 p {uand(o,0x33333333u)};
        U32 q {usrl(o,2u)};
        U32 r {uand(q,0x33333333u)};
        U32 s {uadd(p,r)};
        U32 t {usrl(s,4u)};
        U32 u {uadd(s,t)};
        U32 v {uand(u,0x0f0f0f0fu)};
        U32 w {usrl(v,8u)};
        U32 x {uadd(v,w)};
        U32 y {usrl(x,16u)};
        U32 z {uadd(x,y)};
        return uand(z,0x0000003fu);
    }

};

//------------------------------------------------------------------------------

inline
float
app::gpu::math::half::decode(ushort u) { return conversion::decode(u); }

inline
ushort
app::gpu::math::half::encode(float f) { return conversion::encode(f); }
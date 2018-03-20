#pragma once
#include <type_traits>
#include "half.hpp"
#include "int.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

namespace app::gpu::math {

    template<unsigned N, typename T>
    using vector =
        std::conditional_t<N==2,vector2<T>,
        std::conditional_t<N==3,vector3<T>,
        std::conditional_t<N==4,vector4<T>,void>>>;

    using bool1   = bool;
    using bool2   = vector2<bool>;
    using bool3   = vector3<bool>;
    using bool4   = vector4<bool>;

    using schar   = signed char;
    using schar1  = schar;
    using schar2  = vector2<schar>;
    using schar3  = vector3<schar>;
    using schar4  = vector4<schar>;

    using uchar1  = uchar;
    using uchar2  = vector2<uchar>;
    using uchar3  = vector3<uchar>;
    using uchar4  = vector4<uchar>;

    using short1  = short;
    using short2  = vector2<short>;
    using short3  = vector3<short>;
    using short4  = vector4<short>;

    using ushort1 = ushort;
    using ushort2 = vector2<ushort>;
    using ushort3 = vector3<ushort>;
    using ushort4 = vector4<ushort>;

    using half1   = half;
    using half2   = vector2<half>;
    using half3   = vector3<half>;
    using half4   = vector4<half>;

    using int1    = int;
    using int2    = vector2<int>;
    using int3    = vector3<int>;
    using int4    = vector4<int>;

    using uint1   = uint;
    using uint2   = vector2<uint>;
    using uint3   = vector3<uint>;
    using uint4   = vector4<uint>;

    using float1  = float;
    using float2  = vector2<float>;
    using float3  = vector3<float>;
    using float4  = vector4<float>;

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
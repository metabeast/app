#pragma once
#include "matrix2x.hpp"
#include "matrix3x.hpp"
#include "matrix4x.hpp"

namespace app::gpu::math {

    using half2x2  = matrix2x2<half>;
    using half2x3  = matrix2x3<half>;
    using half2x4  = matrix2x4<half>;

    using half3x2  = matrix3x2<half>;
    using half3x3  = matrix3x3<half>;
    using half3x4  = matrix3x4<half>;

    using half4x2  = matrix4x2<half>;
    using half4x3  = matrix4x3<half>;
    using half4x4  = matrix4x4<half>;

    //--------------------------------------------------------------------------

    using float2x2 = matrix2x2<float>;
    using float2x3 = matrix2x3<float>;
    using float2x4 = matrix2x4<float>;

    using float3x2 = matrix3x2<float>;
    using float3x3 = matrix3x3<float>;
    using float3x4 = matrix3x4<float>;

    using float4x2 = matrix4x2<float>;
    using float4x3 = matrix4x3<float>;
    using float4x4 = matrix4x4<float>;

    //--------------------------------------------------------------------------

    inline
    float4
    operator*(const float4x4& m, const float4& v) {
        // TODO
        return {};
    }

    inline
    float3
    operator*(const float3x3& m, const float3& v) {
        // TODO
        return {};
    }

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
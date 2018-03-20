#pragma once
#include <memory>
#include "options.hpp"

namespace app::gpu {

    enum struct alpha_to_coverage : uint8_t {
        DEFAULT,
        DISABLED,
        ENABLED,
    };

    //--------------------------------------------------------------------------

    enum struct face_culling : uint8_t {
        DEFAULT,
        NONE,
        BACK,
        FRONT,
    };

    //--------------------------------------------------------------------------

    enum struct face_winding : uint8_t {
        DEFAULT,
        CLOCKWISE,
        COUNTER_CLOCKWISE,
    };

    //--------------------------------------------------------------------------

    struct sample_count { uint8_t value; };

    //--------------------------------------------------------------------------

    struct depth_bias             { float value; };
    struct depth_bias_clamp       { float value; };
    struct depth_bias_slope_scale { float value; };

    //--------------------------------------------------------------------------

    struct raster_state {
        alpha_to_coverage alpha_to_coverage      {};
        face_winding      face_winding           {};
        face_culling      face_culling           {};
        uint8_t           sample_count           {};
        float             depth_bias             {};
        float             depth_bias_clamp       {};
        float             depth_bias_slope_scale {};

        app_gpu_options(raster_state);
    };

    //==========================================================================

    inline
    bool
    operator==(const raster_state& a, const raster_state& b) {
        return 0 == memcmp(&a,&b,sizeof(a));
    }

    inline
    bool
    operator!=(const raster_state& a, const raster_state& b) {
        return not operator==(a,b);
    }

    //==========================================================================

    inline
    raster_state&
    operator<<(raster_state& o, alpha_to_coverage v) {
        app_assert(o.alpha_to_coverage == alpha_to_coverage{});
        o.alpha_to_coverage = v;
        return o;
    }

    inline
    raster_state&
    operator<<(raster_state& o, face_winding v) {
        app_assert(o.face_winding == face_winding{});
        o.face_winding = v;
        return o;
    }

    inline
    raster_state&
    operator<<(raster_state& o, face_culling v) {
        app_assert(o.face_culling == face_culling{});
        o.face_culling = v;
        return o;
    }

    inline
    raster_state&
    operator<<(raster_state& o, sample_count v) {
        app_assert(o.sample_count == 0);
        o.sample_count = v.value;
        return o;
    }

    inline
    raster_state&
    operator<<(raster_state& o, depth_bias v) {
        app_assert(o.depth_bias == 0);
        o.depth_bias = v.value;
        return o;
    }

    inline
    raster_state&
    operator<<(raster_state& o, depth_bias_clamp v) {
        app_assert(o.depth_bias_clamp == 0);
        o.depth_bias_clamp = v.value;
        return o;
    }

    inline
    raster_state&
    operator<<(raster_state& o, depth_bias_slope_scale v) {
        app_assert(o.depth_bias_slope_scale == 0);
        o.depth_bias_slope_scale = v.value;
        return o;
    }

} // namespace app::gpu
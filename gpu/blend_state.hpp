#pragma once
#include "blend_factor.hpp"
#include "blend_operation.hpp"
#include "color.hpp"
#include "options.hpp"
#include "texture.hpp"
#include "../detail/assert.hpp"
#include "../detail/unpack.hpp"

namespace app::gpu {

    struct blend_color : rgba32f { using rgba32f::rgba32f; };

    //--------------------------------------------------------------------------

    struct color_write_mask { uint8_t mask; };

    //--------------------------------------------------------------------------

    struct color_target_count { uint8_t count; };

    //--------------------------------------------------------------------------

    struct blend_state {
        rgba32f             blend_color         {};
        uint8_t             color_write_mask    {};
        uint8_t             color_target_count  {};
        color_format        color_format        {};
        depth_format        depth_format        {};

        shader_color_factor shader_color_factor {};
        target_color_factor target_color_factor {};
        color_operation     color_operation     {};

        shader_alpha_factor shader_alpha_factor {};
        target_alpha_factor target_alpha_factor {};
        alpha_operation     alpha_operation     {};

        app_gpu_options(blend_state);
    };

    //==========================================================================

    inline
    bool
    operator==(const blend_state& a, const blend_state& b) {
        return 0 == memcmp(&a,&b,sizeof(a));
    }

    inline
    bool
    operator!=(const blend_state& a, const blend_state& b) {
        return not operator==(a,b);
    }

    //==========================================================================

    inline
    blend_state&
    operator<<(blend_state& b, blend_color v) {
        b.blend_color = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, color_write_mask v) {
        b.color_write_mask = v.mask; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, color_target_count v) {
        b.color_target_count = v.count; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, color_format v) {
        b.color_format = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, depth_format v) {
        b.depth_format = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, shader_color_factor v) {
        b.shader_color_factor = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, target_color_factor v) {
        b.target_color_factor = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, color_operation v) {
        b.color_operation = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, shader_alpha_factor v) {
        b.shader_alpha_factor = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, target_alpha_factor v) {
        b.target_alpha_factor = v; return b;
    }

    inline
    blend_state&
    operator<<(blend_state& b, alpha_operation v) {
        b.alpha_operation = v; return b;
    }

} // namespace app::gpu
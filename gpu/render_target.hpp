#pragma once
#include <cstddef>
#include <cstdint>
#include "color.hpp"
#include "options.hpp"
#include "texture.hpp"

namespace app::gpu {

    struct render_texture     { texture*          _; };
    struct render_mip_level   { uint8_t           _; };
    struct render_array_slice { uint8_t           _; };
    struct render_cube_face   { texture_cube_face _; };
    struct render_depth_plane { uint8_t           _; };

    enum struct render_target_type {
        COLOR_TARGET,
        DEPTH_STENCIL_TARGET,
    };

    template<render_target_type>
    struct render_target {
        texture*          render_texture     {};
        uint8_t           render_mip_level   {};
        uint8_t           render_array_slice {};
        texture_cube_face render_cube_face   {};
        uint8_t           render_depth_plane {};

        app_gpu_options(render_target)
    };

    using color_target =
        render_target<
        render_target_type::COLOR_TARGET>;

    using depth_stencil_target =
        render_target<
        render_target_type::DEPTH_STENCIL_TARGET>;

    //==========================================================================

    template<render_target_type T>
    render_target<T>&
    operator<<(render_target<T>& a, const render_texture t) {
        a.render_texture = t._;
        return a;
    }

    template<render_target_type T>
    render_target<T>&
    operator<<(render_target<T>& a, const render_mip_level l) {
        a.render_mip_level = l._;
        return a;
    }

    template<render_target_type T>
    render_target<T>&
    operator<<(render_target<T>& a, const render_array_slice l) {
        a.render_array_slice = l._;
        return a;
    }

    template<render_target_type T>
    render_target<T>&
    operator<<(render_target<T>& a, const render_cube_face f) {
        a.render_cube_face = f._;
        return a;
    }

    template<render_target_type T>
    render_target<T>&
    operator<<(render_target<T>& a, const render_depth_plane t) {
        a.render_depth_plane = t._;
        return a;
    }

} // namespace app::gpu
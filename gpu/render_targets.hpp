#pragma once
#include <cstddef>
#include <cstdint>
#include "limits.hpp"
#include "render_target.hpp"

namespace app::gpu {

    struct render_targets {
        color_target
        color_targets[MAX_COLOR_TARGETS] {};

        depth_stencil_target
        depth_stencil_target {};

        app_gpu_options(render_targets)
    };

    //--------------------------------------------------------------------------

    render_targets&
    operator<<(render_targets& r, const color_target t) {
        for (auto& rt : r.color_targets) {
            if (not rt.render_texture) { rt = t; return r; }
        }
        app_err("exceeded MAX_COLOR_TARGETS (",MAX_COLOR_TARGETS,")");
        return r;
    }

    render_targets&
    operator<<(render_targets& r, const depth_stencil_target t) {
        if (not r.depth_stencil_target.render_texture) {
            r.depth_stencil_target = t; return r;
        }
        app_err("depth_stencil_target already assigned");
        return r;
    }

} // namespace app::gpu
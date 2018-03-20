#pragma once

namespace app::gpu {

    enum limits {
        MAX_COLOR_TARGETS     =  4,
        MAX_SHADER_BUFFERS    =  4,
        MAX_SHADER_TEXTURES   =  4,
        MAX_UNIFORM_BINDINGS  =  4,
        MAX_VERTEX_ATTRIBUTES = 16,
        MAX_VERTEX_BUFFERS    =  4,
    };

} // namespace app::gpu
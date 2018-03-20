#pragma once
#include "buffer.hpp"
#include "texture.hpp"
#include "pipeline.hpp"
#include "options.hpp"
#include "../detail/declarator_list.hpp"

namespace app::gpu {

    struct index_buffer { buffer* buffer {}; };

    //--------------------------------------------------------------------------

    struct vertex_buffer { buffer* buffer {}; };

    using vertex_buffers =
        detail::declarator_list<buffer*,MAX_SHADER_BUFFERS>;

    //--------------------------------------------------------------------------

    struct vertex_texture { texture* texture; };

    using vertex_textures =
        detail::declarator_list<texture*,MAX_SHADER_TEXTURES>;

    //--------------------------------------------------------------------------

    struct fragment_texture { texture* texture; };

    using fragment_textures =
        detail::declarator_list<texture*,MAX_SHADER_TEXTURES>;

    //--------------------------------------------------------------------------

    struct render_state {
        pipeline*         pipeline          {};
        buffer*           index_buffer      {};
        vertex_buffers    vertex_buffers    {};
        vertex_textures   vertex_textures   {};
        fragment_textures fragment_textures {};

        app_gpu_options(render_state);
    };

    //==========================================================================

    auto&
    operator<<(render_state& r, pipeline* p) {
        app_assert(r.pipeline == nullptr);
        r.pipeline = p;
        return r;
    }

    auto&
    operator<<(render_state& r, index_buffer i) {
        app_assert(r.index_buffer == nullptr);
        r.index_buffer = i.buffer;
        return r;
    }

    auto&
    operator<<(render_state& r, vertex_buffer b) {
        r.vertex_buffers << b.buffer;
        return r;
    }

    auto&
    operator<<(render_state& r, vertex_texture t) {
        r.vertex_textures << t.texture;
        return r;
    }

    auto&
    operator<<(render_state& r, fragment_texture t) {
        r.fragment_textures << t.texture;
        return r;
    }

} // namespace app::gpu
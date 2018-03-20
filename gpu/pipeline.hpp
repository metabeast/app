#pragma once
#include "attribute_stream.hpp"
#include "blend_state.hpp"
#include "depth_stencil_state.hpp"
#include "raster_state.hpp"
#include "uniform_binding.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace app::gpu {

    struct vertex_shader { shader* shader; };

    //--------------------------------------------------------------------------

    struct fragment_shader { shader* shader; };

    //--------------------------------------------------------------------------

    enum struct primitive_type {
        DEFAULT,
        TRIANGLES,
        LINES,
        POINTS,
    };

    //--------------------------------------------------------------------------

    enum struct index_type {
        DEFAULT,
        NONE,
        UINT16,
        UINT32,
    };

    //--------------------------------------------------------------------------

    struct pipeline_options {
        attribute_streams   attribute_streams   {};
        shader*             vertex_shader       {};
        shader*             fragment_shader     {};
        index_type          index_type          {};
        primitive_type      primitive_type      {};
        raster_state        raster_state        {};
        blend_state         blend_state         {};
        depth_stencil_state depth_stencil_state {};

        app_gpu_options(pipeline_options)
    };

    //--------------------------------------------------------------------------

    void destroy(struct pipeline*);

    struct pipeline final : resource {
        using options = pipeline_options;
        void operator delete(void* p) { destroy((pipeline*)p); }
    };

    //==========================================================================

    inline
    pipeline_options&
    operator<<(pipeline_options& o, const attribute_streams& a) {
        app_assert(o.attribute_streams.empty());
        o.attribute_streams = a;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, const attribute_stream& a) {
        o.attribute_streams << a;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, const vertex_shader& s) {
        app_assert(o.vertex_shader == nullptr);
        o.vertex_shader = s.shader;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, const fragment_shader& s) {
        app_assert(o.fragment_shader == nullptr);
        o.fragment_shader = s.shader;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, index_type i) {
        app_assert(o.index_type == index_type{});
        o.index_type = i;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, primitive_type p) {
        app_assert(o.primitive_type == primitive_type{});
        o.primitive_type = p;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, raster_state p) {
        app_assert(o.raster_state == raster_state{});
        o.raster_state = p;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, blend_state b) {
        app_assert(o.blend_state == blend_state{});
        o.blend_state = b;
        return o;
    }

    inline
    pipeline_options&
    operator<<(pipeline_options& o, depth_stencil_state b) {
        app_assert(o.depth_stencil_state == depth_stencil_state{});
        o.depth_stencil_state = b;
        return o;
    }

} // namespace app::gpu
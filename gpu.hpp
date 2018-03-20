#pragma once
#include <cassert>
#include <cstdint>
#include "app.hpp"
#include "gpu/render_state.hpp"
#include "gpu/render_targets.hpp"
#include "gpu/scissor.hpp"
#include "gpu/viewport.hpp"
#include "detail/unique_ptr.hpp"

namespace app::gpu {

    using detail::unique_ptr;

    template<typename resource>
    auto create_unique(const typename resource::options& s) {
        return unique_ptr<resource>(create(s));
    }

    template<typename resource>
    auto create(const typename resource::options& s) {
        return create(s);
    }

    auto create(const   buffer::options&) -> buffer*;
    auto create(const  texture::options&) -> texture*;
    auto create(const   shader::options&) -> shader*;
    auto create(const pipeline::options&) -> pipeline*;

    void destroy(  buffer*);
    void destroy( texture*);
    void destroy(  shader*);
    void destroy(pipeline*);

    //void write(buffer*, const data&);
    //void write(texture*, const subimage&, const data&);
    //void write(uniform_block*, const data&);

    void set(window*);
    //void set(pass*);
    //void set(targets*);
    void set(render_targets*);
    void set(viewport*);
    void set(scissor*);
    void set(pipeline*);
    //void set(index_buffer*);
    //void set(vertex_buffer*, uint count);
    //void set(geometry*);
    //void set(uniforms*);

    //void draw(const draw_options&);
    // void draw(uint offset, uint count, uint instances);

    void present();

} // namespace app::gpu
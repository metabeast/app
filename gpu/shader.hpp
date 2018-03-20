#pragma once
#include <cstddef>
#include <cstring>
#include "options.hpp"
#include "../detail/assert.hpp"
#include "../detail/unpack.hpp"

namespace app::gpu {

    enum struct shader_stage { DEFAULT, VERTEX, FRAGMENT };

    //--------------------------------------------------------------------------

    struct shader_source {
        const void* data {};
        size_t      size {};

        explicit
        shader_source(const char* text):shader_source(text,strlen(text)) {}
        shader_source(const void* data,size_t size):size(size),data(data) {}
        shader_source() = default;
    };

    //--------------------------------------------------------------------------

    struct shader_options {
        shader_stage  shader_stage  {};
        shader_source shader_source {};

        shader_options() = default;
        shader_options(
            const decltype(shader_stage)&  shader_stage,
            const decltype(shader_source)& shader_source)
        :shader_stage  (shader_stage)
        ,shader_source (shader_source) {}
    };

    //--------------------------------------------------------------------------

    void destroy(struct shader*);

    struct shader final : resource {
        using options = shader_options;
        void operator delete(void* p) { destroy((shader*)p); }
    };

    //==========================================================================

    inline
    shader_options&
    operator<<(shader_options& o, const shader_stage& s) {
        app_assert(o.shader_stage == shader_stage::DEFAULT);
        o.shader_stage = s;
        return o;
    }

    inline
    shader_options&
    operator<<(shader_options& o, const shader_source& s) {
        app_assert(o.shader_source.data == nullptr);
        o.shader_source = s;
        return o;
    }

} // namespace app::gpu
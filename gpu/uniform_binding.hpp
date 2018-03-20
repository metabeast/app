#pragma once
#include <cstddef>
#include "limits.hpp"
#include "options.hpp"
#include "texture.hpp"
#include "../detail/assert.hpp"
#include "../detail/declarator_list.hpp"
#include "../detail/resource.hpp"
#include "../detail/unpack.hpp"

namespace app::gpu {

    struct uniform_name { const char* name; };

    struct uniform_size { size_t size; };

    //--------------------------------------------------------------------------

    struct uniform_binding {
        const char* uniform_name {};
        size_t      uniform_size {};

        app_gpu_options(uniform_binding)
    };

    using uniform_bindings =
        detail::declarator_list<uniform_binding,MAX_UNIFORM_BINDINGS>;

    //==========================================================================

    template<typename T>
    const
    uniform_size
    uniform_size_of { sizeof(T) };

    template<typename T>
    struct uniform_binding_of : uniform_binding {
        uniform_binding_of(const char* name)
        :uniform_binding(name,sizeof(T)) {}
    };

    //==========================================================================

    inline
    uniform_binding&
    operator<<(uniform_binding& u, uniform_name n) {
        app_assert(u.uniform_name == nullptr);
        u.uniform_name = n.name;
        return u;
    }

    inline
    uniform_binding&
    operator<<(uniform_binding& u, const char* n) {
        app_assert(u.uniform_name == nullptr);
        u.uniform_name = n;
        return u;
    }

    inline
    uniform_binding&
    operator<<(uniform_binding& u, uniform_size s) {
        app_assert(u.uniform_size == 0);
        u.uniform_size = s.size;
        return u;
    }

    inline
    uniform_binding&
    operator<<(uniform_binding& u, size_t s) {
        app_assert(u.uniform_size == 0);
        u.uniform_size = s;
        return u;
    }

    inline
    uniform_binding&
    operator<<(uniform_binding& u, int s) {
        app_assert(u.uniform_size == 0);
        u.uniform_size = s;
        return u;
    }

} // namespace app::gpu
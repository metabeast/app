#pragma once
#include <cstddef>
#include <cstdint>
#include "options.hpp"
#include "../detail/assert.hpp"
#include "../detail/resource.hpp"
#include "../detail/unpack.hpp"

namespace app::gpu {

    enum struct buffer_access : uint8_t {
        DEFAULT,
        IMMUTABLE,
        DYNAMIC,
        STREAMING,
    };

    //--------------------------------------------------------------------------

    struct buffer_size { size_t size {}; };

    //--------------------------------------------------------------------------

    struct buffer_data { const void* data {}; };

    //--------------------------------------------------------------------------

    struct buffer_options {
        buffer_access buffer_access {};
        size_t        buffer_size   {};
        const void*   buffer_data   {};

        app_gpu_options(buffer_options)
    };

    //--------------------------------------------------------------------------

    void destroy(struct buffer*);

    struct buffer final : resource {
        using options = buffer_options;
        void operator delete(void* p) { destroy((buffer*)p); }
    };

    //==========================================================================

    inline
    buffer_options&
    operator<<(buffer_options& b, buffer_access a) {
        app_assert(b.buffer_access == buffer_access{});
        b.buffer_access = a;
        return b;
    }

    inline
    buffer_options&
    operator<<(buffer_options& b, buffer_size s) {
        app_assert(b.buffer_size == 0);
        b.buffer_size = s.size;
        return b;
    }

    inline
    buffer_options&
    operator<<(buffer_options& b, buffer_data d) {
        app_assert(b.buffer_data == nullptr);
        b.buffer_data = d.data;
        return b;
    }

} // namespace app::gpu
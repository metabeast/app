#pragma once
#include "texture_format.hpp"
#include "../detail/resource.hpp"
#include "../detail/unpack.hpp"

namespace app::gpu {

    enum struct texture_cube_face : uint8_t {
       NEGATIVE_X,
       POSITIVE_X,
       NEGATIVE_Y,
       POSITIVE_Y,
       NEGATIVE_Z,
       POSITIVE_Z,
    };

    //--------------------------------------------------------------------------

    enum struct texture_filter : uint8_t {
        NEAREST,
        LINEAR,
        NEAREST_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_NEAREST,
        LINEAR_MIPMAP_LINEAR,
    };

    //--------------------------------------------------------------------------

    enum struct texture_type : uint8_t {
        DEFAULT,
        PLANE,
        CUBE,
        VOLUME,
        ARRAY,
    };

    //--------------------------------------------------------------------------

    enum struct texture_wrap : uint8_t {
        DEFAULT,
        CLAMP,
        REPEAT,
        MIRROR,
    };

    //--------------------------------------------------------------------------

    struct texture_options {
        // TODO
    };

    //--------------------------------------------------------------------------

    void destroy(struct texture*);

    struct texture final : resource {
        using options = texture_options;
        void operator delete(void* p) { destroy((texture*)p); }
    };

    //==========================================================================

} // namespace app::gpu
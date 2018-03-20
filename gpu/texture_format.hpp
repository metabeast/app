#pragma once
#include <cstdint>

namespace app::gpu {

    enum _texture_format_type { TEXTURE_FORMAT, COLOR_FORMAT, DEPTH_FORMAT };

    template<_texture_format_type>
    struct _texture_format {
        enum struct type : uint8_t {
            DEFAULT,

            RGB8,

            RGBA8,

            R10G10B10A2,
            R5G5B5A1,
            R5G6B5,
            RGBA4,

            RGBA16F,
            RGBA32F,

            R32F,
            R16F,

            L8,

            DXT1,
            DXT3,
            DXT5,

            ETC2_RGB8,
            ETC2_SRGB8,

            PVRTC2_RGB,
            PVRTC4_RGB,
            PVRTC2_RGBA,
            PVRTC4_RGBA,

            DEPTH,
            DEPTH_STENCIL,
        };
    };

    using texture_format = _texture_format<TEXTURE_FORMAT>::type;

    using color_format = _texture_format<COLOR_FORMAT>::type;

    using depth_format = _texture_format<DEPTH_FORMAT>::type;

} // namespace app::gpu
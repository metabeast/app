#pragma once

namespace app::gpu {

    enum struct blend_factor_type {
        SHADER_COLOR_FACTOR,
        SHADER_ALPHA_FACTOR,
        TARGET_COLOR_FACTOR,
        TARGET_ALPHA_FACTOR,
    };

    template<blend_factor_type>
    struct blend_factor {
        enum struct type : uint8_t {
            DEFAULT,

            ZERO,                  // (0,0,0,0)
            ONE,                   // (1,1,1,1)

            SHADER_COLOR,          // (r,g,b,a)
            SHADER_COLOR_INVERSE,  // (1-r,1-g,1-b,1-a)
            SHADER_ALPHA,          // (a,a,a,a)
            SHADER_ALPHA_INVERSE,  // (1-a,1-a,1-a,1-a)

            TARGET_COLOR,          // (r,g,b,a)
            TARGET_COLOR_INVERSE,  // (1-r,1-g,1-b,1-a)
            TARGET_ALPHA,          // (a,a,a,a)
            TARGET_ALPHA_INVERSE,  // (1-a,1-a,1-a,1-a)

            CONSTANT_COLOR,         // (r,g,b,a)
            CONSTANT_COLOR_INVERSE, // (1-r,1-g,1-b,1-a)
            CONSTANT_ALPHA,         // (a,a,a,a)
            CONSTANT_ALPHA_INVERSE, // (1-a,1-a,1-a,1-a)
        };
    };

    using shader_color_factor =
        blend_factor<blend_factor_type::SHADER_COLOR_FACTOR>::type;

    using shader_alpha_factor =
        blend_factor<blend_factor_type::SHADER_ALPHA_FACTOR>::type;

    using target_color_factor =
        blend_factor<blend_factor_type::TARGET_COLOR_FACTOR>::type;

    using target_alpha_factor =
        blend_factor<blend_factor_type::TARGET_ALPHA_FACTOR>::type;

} // namespace app::gpu
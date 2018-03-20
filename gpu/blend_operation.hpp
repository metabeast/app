#pragma once

namespace app::gpu {

    enum struct blend_operation_type {
        COLOR_OPERATION,
        ALPHA_OPERATION,
    };

    template<blend_operation_type>
    struct blend_operation {
        enum struct type : uint8_t {
            DEFAULT,
            TARGET_PLUS_SHADER,  // result = target + shader
            TARGET_MINUS_SHADER, // result = target - shader
            SHADER_MINUS_TARGET, // result = shader - target
        };
    };

    using color_operation =
        blend_operation<blend_operation_type::COLOR_OPERATION>::type;

    using alpha_operation =
        blend_operation<blend_operation_type::ALPHA_OPERATION>::type;

} // namespace app::gpu
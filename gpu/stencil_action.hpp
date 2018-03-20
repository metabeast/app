#pragma once
#include <cstdint>

namespace app::gpu {

    enum struct stencil_action_type {
        DEPTH_FAIL_ACTION,
        STENCIL_FAIL_ACTION,
        DEPTH_STENCIL_PASS_ACTION,
    };

    template<stencil_action_type>
    struct stencil_action {
        enum struct type : uint8_t {
            DEFAULT,
            NONE,
            KEEP,
            ZERO,
            INVERT,
            REPLACE,
            INCREMENT_CLAMP,
            DECREMENT_CLAMP,
            INCREMENT_WRAP,
            DECREMENT_WRAP,
        };
    };

    using depth_fail_action =
        stencil_action<
        stencil_action_type::DEPTH_FAIL_ACTION>::type;

    using stencil_fail_action =
        stencil_action<
        stencil_action_type::STENCIL_FAIL_ACTION>::type;

    using depth_stencil_pass_action =
        stencil_action<
        stencil_action_type::DEPTH_STENCIL_PASS_ACTION>::type;

} // namespace app::gpu
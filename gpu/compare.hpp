#pragma once

namespace app::gpu {

    enum struct compare_type {
        DEPTH_COMPARE,
        STENCIL_COMPARE,
    };

    template<compare_type>
    struct compare {
        enum struct type : uint8_t {
            DEFAULT,
            NEVER,
            NOT_EQUAL,
            LESS,
            LESS_OR_EQUAL,
            EQUAL,
            GREATER_OR_EQUAL,
            GREATER,
            ALWAYS,
        };
    };

    using depth_compare =
        compare<compare_type::DEPTH_COMPARE>::type;

    using stencil_compare =
        compare<compare_type::STENCIL_COMPARE>::type;

} // namespace app::gpu
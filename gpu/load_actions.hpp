#pragma once
#include <cstddef>
#include <cstdint>
#include "color.hpp"
#include "load_action.hpp"
#include "limits.hpp"
#include "options.hpp"
#include "../detail/assert.hpp"
#include "../detail/declarator_list.hpp"

namespace app::gpu {

    using color_load_action = load_action<rgba32f>;

    using color_load_actions =
        detail::declarator_list<color_load_action,MAX_COLOR_TARGETS>;

    //--------------------------------------------------------------------------

    using depth_load_action = load_action<float>;

    //--------------------------------------------------------------------------

    using stencil_load_action = load_action<uint8_t>;

    //--------------------------------------------------------------------------

    struct load_actions {
        color_load_actions  color_load_actions  {};
        depth_load_action   depth_load_action   {};
        stencil_load_action stencil_load_action {};

        app_gpu_options(load_actions);
    };

    //==========================================================================

    inline
    load_actions&
    operator<<(load_actions& l, const color_load_action& a) {
        l.color_load_actions << a;
        return l;
    }

    inline
    load_actions&
    operator<<(load_actions& l, const depth_load_action& a) {
        app_assert(l.depth_load_action.load_operation == load_operation{});
        l.depth_load_action = a;
        return l;
    }

    inline
    load_actions&
    operator<<(load_actions& l, const stencil_load_action& a) {
        app_assert(l.stencil_load_action.load_operation == load_operation{});
        l.stencil_load_action = a;
        return l;
    }

} // namespace app::gpu
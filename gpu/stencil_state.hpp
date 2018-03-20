#pragma once
#include "compare.hpp"
#include "options.hpp"
#include "stencil_action.hpp"

namespace app::gpu {

    enum struct stencil_state_type {
        STENCIL_STATE_BACK,
        STENCIL_STATE_FRONT,
    };

    template<stencil_state_type>
    struct stencil_state {
        stencil_compare        stencil_compare        {};
        depth_fail_action         depth_fail_action         {};
        stencil_fail_action       stencil_fail_action       {};
        depth_stencil_pass_action depth_stencil_pass_action {};

        app_gpu_options(stencil_state)
    };

    using stencil_state_back =
        stencil_state<
        stencil_state_type::STENCIL_STATE_BACK>;

    using stencil_state_front =
        stencil_state<
        stencil_state_type::STENCIL_STATE_FRONT>;

    //==========================================================================

    template<stencil_state_type T>
    stencil_state<T>&
    operator<<(stencil_state<T>& s, stencil_compare c) {
        s.stencil_compare = c;
        return s;
    }

    template<stencil_state_type T>
    stencil_state<T>&
    operator<<(stencil_state<T>& s, depth_fail_action a) {
        s.depth_fail_action = a;
        return s;
    }

    template<stencil_state_type T>
    stencil_state<T>&
    operator<<(stencil_state<T>& s, stencil_fail_action a) {
        s.stencil_fail_action = a;
        return s;
    }

    template<stencil_state_type T>
    stencil_state<T>&
    operator<<(stencil_state<T>& s, depth_stencil_pass_action a) {
        s.depth_stencil_pass_action = a;
        return s;
    }

} // namespace app::gpu
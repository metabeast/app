#pragma once
#include "compare.hpp"
#include "options.hpp"
#include "stencil_state.hpp"

namespace app::gpu {

    enum struct depth_read : uint8_t { DISABLED, ENABLED };

    enum struct depth_write : uint8_t { DISABLED, ENABLED };

    struct stencil_mask_read  { uint8_t _; };

    struct stencil_mask_write { uint8_t _; };

    struct stencil_test_value { uint8_t _; };

    //--------------------------------------------------------------------------

    struct depth_stencil_state {
        depth_compare       depth_compare       {};
        depth_read          depth_read          {};
        depth_write         depth_write         {};
        uint8_t             stencil_mask_read   {};
        uint8_t             stencil_mask_write  {};
        uint8_t             stencil_test_value  {};
        stencil_state_back  stencil_state_back  {};
        stencil_state_front stencil_state_front {};

        app_gpu_options(depth_stencil_state)
    };

    //==========================================================================

    inline
    bool
    operator==(const depth_stencil_state& a, const depth_stencil_state& b) {
        return 0 == memcmp(&a,&b,sizeof(a));
    }

    inline
    bool
    operator!=(const depth_stencil_state& a, const depth_stencil_state& b) {
        return not operator==(a,b);
    }

    //==========================================================================

    inline
    depth_stencil_state&
    operator<<(depth_stencil_state& d, depth_compare v) {
        d.depth_compare = v;
        return d;
    }

    inline
    depth_stencil_state&
    operator<<(depth_stencil_state& d, depth_write v) {
        d.depth_write = v;
        return d;
    }

    inline
    depth_stencil_state&
    operator<<(depth_stencil_state& d, stencil_mask_read v) {
        d.stencil_mask_read = v._;
        return d;
    }

    inline
    depth_stencil_state&
    operator<<(depth_stencil_state& d, stencil_mask_write v) {
        d.stencil_mask_write = v._;
        return d;
    }

    inline
    depth_stencil_state&
    operator<<(depth_stencil_state& d, stencil_test_value v) {
        d.stencil_test_value = v._;
        return d;
    }

    inline
    depth_stencil_state&
    operator<<(depth_stencil_state& d, stencil_state_front v) {
        d.stencil_state_front = v;
        return d;
    }

    inline
    depth_stencil_state&
    operator<<(depth_stencil_state& d, stencil_state_back v) {
        d.stencil_state_back = v;
        return d;
    }

} // namespace app::gpu
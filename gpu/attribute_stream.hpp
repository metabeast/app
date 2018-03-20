#pragma once
#include <cstdint>
#include "attribute_location.hpp"
#include "../detail/assert.hpp"
#include "../detail/declarator_list.hpp"

namespace app::gpu {

    enum struct attribute_interval : uint8_t {
        DEFAULT,
        VERTEX,
        INSTANCE,
        CONSTANT,
    };

    //--------------------------------------------------------------------------

    struct attribute_period { uint8_t period; };

    //--------------------------------------------------------------------------

    struct attribute_stride { uint8_t stride; };

    //--------------------------------------------------------------------------

    struct attribute_stream {
        uint8_t             attribute_stride    {};
        uint8_t             attribute_period    {};
        attribute_interval  attribute_interval  {};
        attribute_locations attribute_locations {};

        app_gpu_options(attribute_stream);
    };

    // MTLBufferLayoutDescriptor
    struct vertex_layout {
        uint8_t            attribute_stride   {};
        attribute_interval attribute_interval {};
        uint8_t            attribute_period   {};
    };

    // MTLVertexAttributeDescriptor
    struct vertex_attribute {
        uint8_t        buffer_index     {};
        uint8_t        attribute_index  {};
        uint8_t        attribute_offset {};
        attribute_type attribute_type   {};
    };

    using vertex_attributes = 
        detail::declarator_list<vertex_attribute, MAX_VERTEX_ATTRIBUTES>;

    struct vertex_buffer_layout {
        uint8_t           buffer_index      {};
        uint8_t           attribute_stride  {};
        vertex_attributes vertex_attributes {};
    };

    struct instance_buffer_layout {
        uint8_t           buffer_index      {};
        uint8_t           attribute_stride  {};
        uint8_t           attribute_period  {};
        vertex_attributes vertex_attributes {};
    };

    //--------------------------------------------------------------------------

    using attribute_streams =
        detail::declarator_list<attribute_stream,MAX_VERTEX_BUFFERS>;

    //==========================================================================

    template<typename T>
    inline const
    attribute_stride
    attribute_stride_of { sizeof(T) };

    //==========================================================================

    inline
    attribute_stream&
    operator<<(attribute_stream& a, attribute_interval i) {
        app_assert(a.attribute_interval == attribute_interval{});
        a.attribute_interval = i;
        return a;
    }

    inline
    attribute_stream&
    operator<<(attribute_stream& a, attribute_period p) {
        app_assert(a.attribute_period == 0);
        a.attribute_period = p.period;
        return a;
    }

    inline
    attribute_stream&
    operator<<(attribute_stream& a, attribute_stride s) {
        app_assert(a.attribute_stride == 0);
        a.attribute_stride = s.stride;
        return a;
    }

    inline
    attribute_stream&
    operator<<(attribute_stream& a, attribute_location l) {
        a.attribute_locations << l;
        return a;
    }

} // namespace app::gpu
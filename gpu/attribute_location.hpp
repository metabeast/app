#pragma once
#include <cstdint>
#include "limits.hpp"
#include "options.hpp"
#include "math/matrix.hpp"
#include "math/vector.hpp"
#include "../detail/assert.hpp"
#include "../detail/declarator_list.hpp"

namespace app::gpu {

    struct attribute_name { const char* name; };

    //--------------------------------------------------------------------------

    enum struct attribute_type : uint8_t {
        NONE,
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        SCHAR4,
        SCHAR4N,
        UCHAR4,
        UCHAR4N,
        SHORT2,
        SHORT2N,
        SHORT4,
        SHORT4N,
    };

    //--------------------------------------------------------------------------

    struct attribute_offset { uint8_t offset; };

    //--------------------------------------------------------------------------

    struct attribute_index { uint8_t index; };

    //--------------------------------------------------------------------------

    struct attribute_location {
        const char*     attribute_name   {};
        attribute_type  attribute_type   {};
        uint8_t         attribute_offset {};
        uint8_t         attribute_index  {};

        app_gpu_options(attribute_location)
    };

    //--------------------------------------------------------------------------

    using attribute_locations =
        detail::declarator_list<attribute_location,MAX_VERTEX_ATTRIBUTES>;

    //==========================================================================

    template<typename T, typename Struct, T Struct::*Member>
    attribute_name
    attribute_name_of_() {
        static const char* const name = [](const char* p){
            static char buffer[32] {};
            #if app_compiler_clang
                p = strstr(p,"Member = &")+strlen("Member = &");
                while (auto q = strstr(p,"::")) p = q+strlen("::");
            #else
                app_todo("attribute_name_of_() is compiler-specific")
            #endif
            strncpy(buffer,p,strlen(p)-strlen("]"));
            return buffer;
        }(__PRETTY_FUNCTION__);
        return {name};
    }

    template<auto>
    const
    decltype(nullptr)
    attribute_name_of {};

    template<typename T, typename Struct, T Struct::*Member>
    const
    attribute_name
    attribute_name_of<Member> { attribute_name_of_<T,Struct,Member>() };

    //--------------------------------------------------------------------------

    template<typename T, typename Struct, T Struct::*Member>
    attribute_type
    attribute_type_of_() {
        if constexpr(std::is_same_v<T,float1>)
            return attribute_type::FLOAT;
        if constexpr(std::is_same_v<T,float2>)
            return attribute_type::FLOAT2;
        if constexpr(std::is_same_v<T,float3>)
            return attribute_type::FLOAT3;
        if constexpr(std::is_same_v<T,float4>)
            return attribute_type::FLOAT4;
        if constexpr(std::is_same_v<T,schar4>)
            return attribute_type::SCHAR4;
        if constexpr(std::is_same_v<T,uchar4>)
            return attribute_type::UCHAR4;
        if constexpr(std::is_same_v<T,short2>)
            return attribute_type::SHORT2;
        if constexpr(std::is_same_v<T,short4>)
            return attribute_type::SHORT4;
        app_err("unsupported type");
        return attribute_type::NONE;
    }

    template<auto>
    const
    decltype(nullptr)
    attribute_type_of {};

    template<typename T, typename Struct, T Struct::*Member>
    const
    attribute_type
    attribute_type_of<Member> { attribute_type_of_<T,Struct,Member>() };

    //--------------------------------------------------------------------------

    template<typename T, typename Struct, T Struct::*Member>
    attribute_offset
    attribute_offset_of_() {
        return { uint8_t(size_t(&(((Struct*)nullptr)->*Member))) };
    }

    template<auto>
    const
    decltype(nullptr)
    attribute_offset_of {};

    template<typename T, typename Struct, T Struct::*Member>
    const
    attribute_offset
    attribute_offset_of<Member> { attribute_offset_of_<T,Struct,Member>() };

    //--------------------------------------------------------------------------

    template<auto>
    const
    decltype(nullptr)
    attribute_location_of {};

    template<typename T, typename Struct, T Struct::*Member>
    const
    attribute_location
    attribute_location_of<Member> {
        attribute_name_of<Member>,
        attribute_type_of<Member>,
        attribute_offset_of<Member>,
    };

    //==========================================================================

    inline
    attribute_location&
    operator<<(attribute_location& a, attribute_name n) {
        app_assert(not a.attribute_name);
        a.attribute_name = n.name;
        return a;
    }

    inline
    attribute_location&
    operator<<(attribute_location& a, const char* n) {
        app_assert(not a.attribute_name);
        a.attribute_name = n;
        return a;
    }

    inline
    attribute_location&
    operator<<(attribute_location& a, attribute_type t) {
        app_assert(a.attribute_type == attribute_type::NONE);
        a.attribute_type = t;
        return a;
    }

    inline
    attribute_location&
    operator<<(attribute_location& a, attribute_offset o) {
        app_assert(a.attribute_offset == 0);
        a.attribute_offset = o.offset;
        return a;
    }

    inline
    attribute_location&
    operator<<(attribute_location& a, attribute_index i) {
        app_assert(a.attribute_index == 0);
        app_assert(i.index < MAX_VERTEX_ATTRIBUTES);
        a.attribute_index = i.index;
        return a;
    }

    inline
    attribute_location&
    operator<<(attribute_location& a, int i) {
        app_assert(a.attribute_index == 0);
        app_assert(i >= 0);
        app_assert(i < MAX_VERTEX_ATTRIBUTES);
        a.attribute_index = uint8_t(i);
        return a;
    }

} // namespace app::gpu
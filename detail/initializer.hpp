#pragma once
#include <type_traits>
#include "assert.hpp"

namespace app {

    template<auto>
    struct initializer;

    template<typename T, typename Struct, T Struct::*Member>
    struct initializer<Member> {
        using value_type = std::decay_t<T>;
        value_type value;
    };

    template<typename T, typename Struct, T Struct::*Member>
    Struct& operator<<(Struct& s, const initializer<Member>& i) {
        using value_type = typename decltype(i)::value_type;
        const value_type default_value {};
        if constexpr(std::is_array_v<T>) {
            auto& array = s.*Member;
            for (auto& element : array) {
                const bool element_has_default_value {
                    not memcmp(element, default_value, sizeof(value_type))
                };
                if (element_has_default_value) {
                    element = i.value;
                    return s;
                }
            }
            app_err("array element initializer exceeded array length");
        } else {
            auto& field = s.*Member;
            const bool field_has_default_value {
                not memcmp(field, default_value, sizeof(value_type))
            };
            if (field_has_default_value) {
                field = i.value;
                return s;
            }
            app_err("field already initialized");
        }
        return s;
    }

} // namespace app
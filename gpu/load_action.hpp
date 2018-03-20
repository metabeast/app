#pragma once
#include <cstddef>
#include <cstdint>

namespace app::gpu {

    enum struct load_operation : uint8_t {
        NONE,
        CLEAR,
        DISCARD,
        PRESERVE,
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct load_action {
        load_operation load_operation {};
        T              load_value     {};

        load_action() = default;

        load_action(load_operation load_operation)
        :load_operation(load_operation) {}

        load_action(T load_value)
        :load_operation(load_operation::CLEAR)
        ,load_value(load_value) {}

        struct clear;
        static const clear       CLEAR;
        static const load_action DISCARD;
        static const load_action PRESERVE;
    };

    //--------------------------------------------------------------------------

    template<typename T>
    struct load_action<T>::clear : load_action {
        clear():load_action(load_operation::CLEAR) {}
        clear(T load_value):load_action(load_value) {}
    };

    //--------------------------------------------------------------------------

    template<typename T>
    inline const typename
    load_action<T>::clear
    load_action<T>::CLEAR;

    template<typename T>
    inline const
    load_action<T>
    load_action<T>::DISCARD  { load_operation::DISCARD  };

    template<typename T>
    inline const
    load_action<T>
    load_action<T>::PRESERVE { load_operation::PRESERVE };

} // namespace app::gpu
#pragma once
#include <type_traits>

namespace app::detail {

    template<typename T, bool IsEnum = std::is_enum_v<T>>
    struct fundamental_type;

    template<typename T>
    struct fundamental_type<T,/*IsEnum*/false> {
        using type = std::conditional_t<std::is_fundamental_v<T>,T,void>;
    };

    template<typename T>
    struct fundamental_type<T,/*IsEnum*/true> {
        using type = std::underlying_type_t<T>;
    };

    template<typename T>
    using fundamental_type_t = typename fundamental_type<T>::type;

} // namespace app::detail
#pragma once
#include <sstream>
#include "unpack.hpp"

namespace app::detail {

    template<typename... Args>
    std::string
    format(Args&&... args) {
        std::stringstream s;
        app_unpack(s << args);
        return s.str();
    }

} // namespace app::detail
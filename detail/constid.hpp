#pragma once
#include "fnv1a.hpp"

namespace app::detail {

    inline
    constexpr uint32_t
    constid32(const char* const s, const uint32_t value = fnv1a32::basis) {
        return s[0] ? constid32(&s[1],(value ^ s[0]) * fnv1a32::prime) : value;
    }

    inline
    constexpr uint64_t
    constid64(const char* const s, const uint64_t value = fnv1a64::basis) {
        return s[0] ? constid64(&s[1],(value ^ s[0]) * fnv1a64::prime) : value;
    }

}


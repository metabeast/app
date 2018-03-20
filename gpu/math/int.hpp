#pragma once
#include <cstdint>

namespace app::gpu::math {

    static_assert(sizeof(short) == 2,"expected 16-bit short");
    static_assert(sizeof(int)   == 4,"expected 32-bit int");

    using uchar  = unsigned char;
    using ushort = unsigned short;
    using uint   = unsigned int;

} // namespace app::gpu::math

namespace app::gpu { using namespace app::gpu::math; }
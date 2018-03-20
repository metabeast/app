#pragma once

namespace app::detail {

    struct callsite;

    template<auto MaxSize>
    class callstack {

        callsite* _callsites[MaxSize] {};

    public:

        callstack(const size_t skip = 0);

    };


} // namespace app::detail
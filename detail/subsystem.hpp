#pragma once

namespace app::detail {

    struct subsystem final {

        using delegate = void(*)();

    private:

        friend struct subsystems;
        static inline subsystem* _first {};
        static inline subsystem* _last  {};

        subsystem* _prev {};
        subsystem* _next {};

        const delegate _startup  {};
        const delegate _shutdown {};

    public:

        subsystem(delegate startup, delegate shutdown)
        :_startup(startup)
        ,_shutdown(shutdown) {
            if (_first) {
                _prev = _last;
                _prev->_next = this;
                _last = this;
            } else {
                _first = _last = this;
            }
        }

    };

} // namespace app::detail
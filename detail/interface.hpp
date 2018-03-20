#pragma once

namespace app {

    class interface {
    protected:
        interface()                              = default;
        interface(interface&&)                   = delete;
        interface(const interface&)              = delete;
        interface& operator = (interface&&)      = delete;
        interface& operator = (const interface&) = delete;
        virtual ~interface()                     = default;
    };

} // namespace app
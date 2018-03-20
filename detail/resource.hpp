#pragma once

namespace app {

    class resource {
        resource()                             = delete;
        resource(resource&&)                   = delete;
        resource(const resource&)              = delete;
        resource& operator = (resource&&)      = delete;
        resource& operator = (const resource&) = delete;
    };

} // namespace app
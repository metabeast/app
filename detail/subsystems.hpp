#pragma once
#include "assert.hpp"
#include "subsystem.hpp"

namespace app::detail {

    struct subsystems {

        subsystems() {
            static unsigned startup_counter {};
            startup_counter += 1;
            app_assert(startup_counter == 1);
            const subsystem* itr {subsystem::_first};
            for (;itr;itr->_startup(),itr=itr->_next);
        }

        ~subsystems() {
            static unsigned shutdown_counter {};
            shutdown_counter += 1;
            app_assert(shutdown_counter == 1);
            const subsystem* itr {subsystem::_last};
            for (;itr;itr->_shutdown(),itr=itr->_prev);
        }

    };

} // namespace app::detail
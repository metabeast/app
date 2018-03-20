#pragma once
#include "../detail/format.hpp"
#include "diagnostic.hpp"
#include "sequence.hpp"

namespace app::gpuc {

    using detail::format;

    struct diagnostics : sequence<diagnostic> {
        const substring source {};

        diagnostics() = default;
        diagnostics(diagnostics&&) = default;
        diagnostics& operator=(diagnostics&&) = default;

        diagnostics(const char* source)
        :source(source) {}

        template<typename... Args>
        void note(substring location, Args&&... args) {
            append({
                diagnostic_level::NOTE,
                substring(source),
                substring(location),
                format(args...),
            });
        }

        template<typename... Args>
        void warning(substring location, Args&&... args) {
            append({
                diagnostic_level::WARNING,
                substring(source),
                substring(location),
                format(args...),
            });
        }

        template<typename... Args>
        void error(substring location, Args&&... args) {
            append({
                diagnostic_level::ERROR,
                substring(source),
                substring(location),
                format(args...),
            });
        }

        void append(diagnostic new_diagnostic) {
            for (const auto& old_diagnostic : *this) {
                if (new_diagnostic == old_diagnostic)
                    return;
            }
            operator<<(std::move(new_diagnostic));
        }

    };

    inline std::ostream& operator<<(std::ostream& o, const diagnostics& s) {
        for (auto& d : s) o << d;
        return o;
    }

} // namespace app::gpuc
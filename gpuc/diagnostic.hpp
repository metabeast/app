#pragma once
#include <iostream>
#include "../detail/substring.hpp"

namespace app::gpuc {

    using detail::substring;

    enum struct diagnostic_level { NOTE, WARNING, ERROR };

    struct diagnostic {
        const diagnostic_level level;
        const substring        source;
        const substring        location;
        const std::string      message;

        diagnostic() = default;
        diagnostic(diagnostic&&) = default;
        diagnostic(const diagnostic&) = default;
        diagnostic& operator=(diagnostic&&) = default;
        diagnostic& operator=(const diagnostic& x) = default;

        diagnostic(
            diagnostic_level level,
            substring source,
            substring location,
            std::string message)
        :level(level)
        ,source(source)
        ,location(location)
        ,message(message) {}
        
        friend
        bool operator==(const diagnostic& a, const diagnostic& b) {
            return not(a != b);
        }
        
        friend
        bool operator!=(const diagnostic& a, const diagnostic& b) {
            return a.level != b.level
                or a.source != b.source
                or a.location != b.location
                or a.message != b.message;
        }
    };

    inline std::ostream& operator<<(std::ostream& o, const diagnostic& d) {
        // TODO: read filename from #line directives
        const char* context_begin = d.source.begin();
        const char* context_end = d.source.end();
        const auto location = d.location.begin();
        unsigned line = 0, column = 0;
        if (location >= context_begin and location < context_end) {
            line = 1; column = 1;
            for (auto src = context_begin; src < location; ++src) {
                if (src[0] == '\n') {
                    line += 1;
                    column = 1;
                    context_begin = src+1;
                }
                else { column += 1; }
            }
            o << line << ":" << column;
        }
        switch (d.level) {
            case diagnostic_level::NOTE:
                o << ": note: "; break;
            case diagnostic_level::WARNING:
                o << ": warning: "; break;
            case diagnostic_level::ERROR:
                o << ": error: "; break;
        }
        o << d.message << "\n";
        if (line and column) {
            context_end = context_begin;
            for (; context_end < d.source.end(); ++context_end) {
                if (context_end[0] == '\n') break;
            }
            substring context(context_begin,context_end);
            o << context << "\n";
            for (unsigned i = 1; i < column; o<<" ",++i);
            for (unsigned i = 0; i < d.location.size(); o<<"^",++i);
        }
        return o;
    }

} // namespace app::gpuc
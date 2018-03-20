#pragma once
#include "parser.hpp"

namespace app::gpuc {

    struct tree : private parser {
        tree() = default;
        tree(tree&&) = default;
        tree& operator=(tree&&) = default;

        tree(const char* source)
        :parser(source) {}

        const auto& diagnostics() {
            return *static_cast<gpuc::diagnostics*>(this);
        }

        const_sequence<lexeme>& lexemes() {
            return parser::lexemes;
        }

        const node_ptr& root() {
            return parser::root;
        }
    };

} // namespace app::gpuc
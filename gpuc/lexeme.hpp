#pragma once
#include "../detail/assert.hpp"
#include "../detail/substring.hpp"
#include "token.hpp"

namespace app::gpuc {

    using detail::substring;

    struct lexeme {
        enum : uint16_t { max_length = 0xFFFFu };
        const char* const head {""};
        const uint16_t    length {};
        const token       token {};

        lexeme() = default;

        lexeme(const lexeme&) = default;
        lexeme& operator=(const lexeme& s) {
            return *new(this)lexeme(s);
        }

        lexeme(lexeme&& s):lexeme(s) { new(&s)lexeme(); }
        lexeme& operator=(lexeme&& s) {
            if (this != &s) new(this)lexeme(std::move(s));
            return *this;
        }

        lexeme(const char* head, size_t length, enum token token)
        :head(head)
        ,length(uint16_t((app_assert(length < max_length),length)))
        ,token(token) {}

        lexeme(const char* head, const char* tail, enum token token)
        :lexeme(head,std::distance(head,tail),token) {}

        lexeme(const char* s, enum token token)
        :lexeme(s,strlen(s),token) {}

        explicit operator bool() const { return token != token::END; }

        operator enum token() const { return token; }

        operator substring() const { return {head,length}; }

        auto operator[](size_t i) const { return i < length ? head[i] : 0; }

        auto begin() const { return head; }
        auto   end() const { return head + length; }

        auto empty() const { return length == 0; }
        auto  size() const { return length; }

        auto front() const { return operator[](0); }
        auto  back() const { return operator[](length-1); }

        friend bool operator==(const lexeme& a, const lexeme& b) {
            return not operator!=(a,b);
        }

        friend bool operator!=(const lexeme& a, const lexeme& b) {
            return (a.length!=b.length) or strncmp(a.head,b.head,b.length);
        }

        friend std::ostream& operator<<(std::ostream& o, const lexeme& s) {
            return o.write(s.head,s.length);
        }

        friend std::ostream& operator<<(std::ostream& o, const lexeme* s) {
            return s ? o << *s : o << "<null>";
        }
    };

} // namespace app::gpuc
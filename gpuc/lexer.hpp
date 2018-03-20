#pragma once
#include "diagnostics.hpp"
#include "lexeme.hpp"

namespace app::gpuc {

    struct lexer : diagnostics {
        sequence<lexeme> lexemes {};

        lexer(const char* source)
        :diagnostics(source) { lex(); }

    private:
        using itr_t = const char*;
        using end_t = const char* const;

        #define app_gpuc_token_constexpr(TOKEN,...)\
            static constexpr token TOKEN = token::TOKEN;
        app_gpuc_token(app_gpuc_token_constexpr)
        #undef app_gpuc_token_alias

        void lex() {
            const auto lexeme_count_estimate = source.size()/4;
            lexemes.reserve(lexeme_count_estimate);
            itr_t itr = source.begin();
            end_t end = source.end();
            while(lex(itr,end));
        }

        void error(itr_t itr, end_t end, const char* message) {
            diagnostics::error(substring(itr,end),message);
        }

        void lexeme(itr_t itr, end_t end, token token) {
            lexemes << gpuc::lexeme(itr,end,token);
        }

    private:
        bool lex(itr_t& itr, end_t end) {
            skip_nontokens(itr,end);
            if (itr < end) {
                return read_identifier(itr,end)
                    or read_number(itr,end)
                    or read_symbol(itr,end);
            }
            return false;
        }

        bool read_identifier(itr_t& itr, end_t end) {
            auto ptr = itr;
            if (skip(ptr,end,'_',isalpha)) {
                while (skip(ptr,end,'_',isalnum));
                lexeme(itr,ptr,[&]{
                    #define app_gpuc_match_keyword(KEYWORD,string)\
                        if (match(itr,ptr,string))\
                            return token::KEYWORD;
                    app_gpuc_token_keyword(app_gpuc_match_keyword)
                    app_gpuc_token_typename(app_gpuc_match_keyword)
                    #undef app_gpuc_match_keyword
                    return token::IDENTIFIER;
                }());
                itr = ptr;
                return true;
            }
            return false;
        }

        bool read_number(itr_t& itr, end_t end) {
            enum token token = INT_LITERAL;
            auto ptr = itr;
            if (skip(ptr,end,isdigit)) {
                while (skip(ptr,end,isdigit));
                if (skip(ptr,end,'.')) {
                    while (skip(ptr,end,isdigit));
                    token = DOUBLE_LITERAL;
                }
                if (skip(ptr,end,"e+","e-","E+","E-",'e','E')) {
                    while (skip(ptr,end,isdigit));
                    token = DOUBLE_LITERAL;
                }
                if (token == DOUBLE_LITERAL) {
                    if (skip(ptr,end,'f','F'))
                        token = FLOAT_LITERAL;
                } else {
                    if (skip(ptr,end,'f','F'))
                        token = FLOAT_LITERAL;
                    else
                    if (skip(ptr,end,'u','U'))
                        token = UINT_LITERAL;
                }
                auto suffix = ptr;
                if (skip(ptr,end,'.','_',isalnum)) {
                    while (skip(ptr,end,'.','_',isalnum));
                    error(suffix,ptr,"invalid number suffix");
                }
                lexeme(itr,ptr,token);
                itr = ptr;
                return true;
            }
            return false;
        }

        bool read_symbol(itr_t& itr, end_t end) {
            auto ptr = itr;
            #define app_gpuc_skip_symbol(SYMBOL,string)\
                if (skip(ptr,end,string)) {\
                    lexeme(itr,ptr,token::SYMBOL);\
                    itr = ptr;\
                    return true;\
                }
            app_gpuc_token_symbol(app_gpuc_skip_symbol)
            #undef app_gpuc_skip_symbol
            if (itr < end) {
                error(itr,itr+1,"invalid symbol");
            }
            return false;
        }

        template<typename Arg>
        static
        bool match(itr_t itr, end_t end, Arg&& arg) {
            return skip(itr,end,arg) and itr == end;
        }

        static
        char peek(itr_t& itr, end_t end) {
            return itr < end ? *itr : 0;
        }

        static
        bool peek(itr_t& itr, end_t end, char c) {
            return itr < end and c == *itr;
        }

        template<typename Bool, typename Char>
        static
        bool peek(itr_t itr, end_t end, Bool(&f)(Char)) {
            return itr < end and f(*itr);
        }

        static
        bool seek(itr_t& itr, end_t end, char c) {
            auto* p = itr;
            for (;p < end;++p) if (c == *p) { itr = p; return true; }
            return false;
        }

        static
        bool seek(itr_t& itr, end_t end, const char* s) {
            auto* p = itr;
            if (*s and seek(p,end,*s)) {
                auto* q = p;
                if (skip(q,end,s)) { itr = p; return true; }
            }
            return false;
        }

        static
        bool skip(itr_t& itr, end_t end, char c) {
            auto* p = itr;
            if (peek(p,end,c)) { ++itr; return true; }
            return false;
        }

        static
        bool skip(itr_t& itr, end_t end, const char* s) {
            auto* p = itr;
            for (;*s and peek(p,end,*s);++p,++s);
            if (not *s) { itr = p; return true; }
            return false;
        }

        template<typename Bool, typename Char>
        static
        bool skip(itr_t& itr, end_t end, Bool(&f)(Char)) {
            auto* p = itr;
            if (peek(p,end,f)) { ++itr; return true; }
            return false;
        }

        template<typename A, typename... B>
        static
        bool skip(itr_t& itr, end_t end, A&& a, B&&... b) {
            return skip(itr,end,a) or skip(itr,end,b...);
        }

        bool skip_nontokens(itr_t& itr, end_t end) {
            if (skip_nontoken(itr,end)) {
                while (skip_nontoken(itr,end));
                return true;
            }
            return false;
        }

        bool skip_nontoken(itr_t& itr, end_t end) {
            const bool is_newline {
                itr == source.begin() or
                peek(itr,end,'\n') or
                itr[-1] == '\n'
            };
            if (skip_whitespace(itr,end)) {
                if (is_newline) skip_directive(itr,end);
                return true;
            }
            return is_newline and skip_directive(itr,end);
        }

        bool skip_directive(itr_t& itr, end_t end) {
            auto ptr = itr;
            if (skip(ptr,end,'#')) {
                seek_newline(ptr,end);
                itr = ptr;
                return true;
            }
            return false;
        }

        bool skip_whitespace(itr_t& itr, end_t end) {
            if (skip(itr,end,isspace)) {
                while (skip(itr,end,isspace));
                return true;
            }
            return skip_comment(itr,end);
        }

        bool skip_comment(itr_t& itr, end_t end) {
            return skip_block_comment(itr,end)
                or skip_line_comment(itr,end);
        }

        bool skip_block_comment(itr_t& itr, end_t end) {
            auto ptr = itr;
            if (skip(ptr,end,"/*")) {
                if (seek(ptr,end,"*/") and skip(ptr,end,"*/")) {
                    itr = ptr;
                    return true;
                }
                error(itr,ptr,"unterminated block comment");
                itr = end;
                return true;
            }
            return false;
        }

        bool skip_line_comment(itr_t& itr, end_t end) {
            if (skip(itr,end,"//")) {
                seek_newline(itr,end);
                return true;
            }
            return false;
        }

        void seek_newline(itr_t& itr, end_t end) {
            while (seek(itr,end,'\n')) {
                const bool line_continuation(itr[-1] == '\\');
                skip(itr,end,'\n');
                if (not line_continuation)
                    return;
            }
            itr = end;
        }
    };

} // namespace app::gpuc
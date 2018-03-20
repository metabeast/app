#pragma once

namespace app::detail::parsing {

    using itr_t = const char*;
    using end_t = const char* const;

    inline char peek(itr_t itr, end_t end) {
        return itr < end ? *itr : 0;
    }

    template<typename Bool, typename Char>
    inline bool peek(itr_t itr, end_t end, Bool(&f)(Char)) {
        return itr < end and f(*itr);
    }

    inline bool peek(itr_t itr, end_t end, char c) {
        return itr < end and c == *itr;
    }

    inline bool peek(itr_t itr, end_t end, const char* s) {
        auto* p = itr;
        for (;*s and peek(p,end,*s);++p,++s);
        if (not *s) { return true; }
        return false;
    }

    //--------------------------------------------------------------------------

    template<typename Bool, typename Char>
    inline bool skip(itr_t& itr, end_t end, Bool(&f)(Char)) {
        auto* p = itr;
        if (peek(p,end,f)) { ++itr; return true; }
        return false;
    }

    inline bool skip(itr_t& itr, end_t end, char c) {
        auto* p = itr;
        if (peek(p,end,c)) { ++itr; return true; }
        return false;
    }

    inline bool skip(itr_t& itr, end_t end, const char* s) {
        auto* p = itr;
        for (;*s and peek(p,end,*s);++p,++s);
        if (not *s) { itr = p; return true; }
        return false;
    }

    template<typename A, typename... B>
    inline bool skip(itr_t& itr, end_t end, A&& a, B&&... b) {
        return skip(itr,end,a) or skip(itr,end,b...);
    }

    //--------------------------------------------------------------------------

    inline bool seek(itr_t& itr, end_t end, char c) {
        auto* p = itr;
        for (;p < end;++p) if (c == *p) { itr = p; return true; }
        return false;
    }

    inline bool seek(itr_t& itr, end_t end, const char* s) {
        auto* p = itr;
        if (*s and seek(p,end,*s)) {
            auto* q = p;
            if (skip(q,end,s)) { itr = p; return true; }
        }
        return false;
    }

    //--------------------------------------------------------------------------

    inline bool seek_and_skip(itr_t& itr, end_t end, char c) {
        auto* p = itr;
        if (seek(p,end,c) and skip(p,end,c)) { itr = p; return true; }
        return false;
    }

    inline bool seek_and_skip(itr_t& itr, end_t end, const char* s) {
        auto* p = itr;
        if (seek(p,end,s) and skip(p,end,s)) { itr = p; return true; }
        return false;
    }

} // namespace app::detail::parsing

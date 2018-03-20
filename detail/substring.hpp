#pragma once
#include <functional>
#include "fnv1a.hpp"

namespace app::detail {

    class substring {
        const char* const _data {};
        const size_t      _size {};

    public:
        substring() = default;

        substring(const substring&) = default;
        substring& operator=(const substring& s) {
            return *new(this)substring(s);
        }

        substring(substring&& s):substring(s) { new(&s)substring(); }
        substring& operator=(substring&& s) {
            if (this != &s) new(this)substring(std::move(s));
            return *this;
        }

        substring(const char* str)
        :substring(str,strlen(str)) {}

        substring(const char* data, size_t size)
        :_data(data),_size(size) {}

        substring(const char* head, const char* tail)
        :_data(head),_size(std::distance(head,tail)) {}

        auto operator[](size_t i) const { return i < _size ? _data[i] : 0; }

        auto begin() const { return _data; }
        auto   end() const { return _data + _size; }

        auto empty() const { return _size == 0; }
        auto  size() const { return _size; }

        auto front() const { return operator[](0); }
        auto  back() const { return operator[](_size-1); }

        auto& write(std::ostream& o) const { return o.write(_data,_size); }

        friend bool operator==(const substring& a, const substring& b) {
            return not operator!=(a,b);
        }
        friend bool operator!=(const substring& a, const substring& b) {
            return (a._size!=b._size) or strncmp(a._data,b._data,b._size);
        }
        friend std::ostream& operator<<(std::ostream& o, const substring& s) {
            return s.write(o);
        }

        size_t hash() const { return detail::fnv1a<size_t>(_data,_size); }
    };

} // namespace app::detail

template<>
struct std::hash<app::detail::substring> {
    size_t operator()(const app::detail::substring& s) const {
        return s.hash();
    }
};
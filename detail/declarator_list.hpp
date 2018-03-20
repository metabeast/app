#pragma once
#include <algorithm>
#include <initializer_list>
#include "fundamental_type.hpp"

namespace app::detail {

    template<typename T, auto MaxSize, typename SizeType = size_t>
    struct declarator_list {

        using value_type      = T;
        using size_type       = SizeType;
        using const_reference = const T&;
        using reference       = T&;
        using const_pointer   = const T*;
        using pointer         = T*;
        using const_iterator  = const T*;
        using iterator        = T*;

    private:

        enum : size_type { _max_size = size_type(MaxSize) };

        size_type _size    {};
        T _data[_max_size] {};

    public:

        declarator_list() = default;

        declarator_list(std::initializer_list<T> l) {
            for (auto& t : l) operator<<(t);
        }

    public: // operators

        auto& operator[](size_type i) const {
            app_assert(i < _size);
            return _data[i];
        }

        auto& operator<<(const T& t) {
            app_assert(_size < _max_size);
            _data[_size++] = t;
            return *this;
        }

        friend
        bool operator==(const declarator_list& a, const declarator_list& b) {
            return
                a.size() == b.size() and
                std::equal(a.begin(),a.end(),b.begin(),b.end());
        }

        friend
        bool operator!=(const declarator_list& a, const declarator_list& b) {
            return not operator==(a,b);
        }

    public: // properties

        bool empty() const { return not _size; }

        auto size() const { return _size; }

        auto max_size() const { return _max_size; }

    public: // iterators

        auto* begin() const { return _data; }

        auto* end() const { return _data + _size; }

    };

} // namespace app::detail
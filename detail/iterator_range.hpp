#pragma once
#include <iterator>

namespace app::detail {

    template<typename Iterator>
    class iterator_range {
        Iterator _begin {}, _end {};

    public:
        iterator_range() = default;
        iterator_range(Iterator begin, Iterator end)
        :_begin(begin),_end(end) {}

        explicit operator bool() const { return _begin != _end; }

        auto begin() const { return _begin; }
        auto   end() const { return _end;   }
        auto empty() const { return _begin == _end; }
        auto  size() const { return std::distance(_begin,_end); }
    };

    template<typename Iterable>
    auto reverse(const Iterable& iterable)
    ->iterator_range<decltype(std::rbegin(iterable))> {
        return {std::rbegin(iterable),std::rend(iterable)};
    }

} // namespace app::detail
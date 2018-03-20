#pragma once
#include <vector>
#include "../detail/assert.hpp"

namespace app::gpuc {

    template<typename T>
    struct sequence : private std::vector<T> {
        sequence() = default;
        sequence(sequence&&) = default;
        sequence& operator=(sequence&&) = default;

        explicit operator bool() const {
            return not empty();
        }

        void operator<<(T&& t) {
            std::vector<T>::emplace_back(std::move(t));
        }

        T& operator[](size_t i) {
            app_assert(i < size());
            return std::vector<T>::operator[](i);
        }

        const T& operator[](size_t i) const {
            app_assert(i < size());
            return std::vector<T>::operator[](i);
        }

        using std::vector<T>::data;
        using std::vector<T>::capacity;
        using std::vector<T>::reserve;
        using std::vector<T>::empty;
        using std::vector<T>::size;
        using std::vector<T>::begin;
        using std::vector<T>::end;
        using std::vector<T>::front;
        using std::vector<T>::back;
    };

    template<typename T>
    struct const_sequence : private sequence<T> {
        const_sequence() = default;
        const_sequence(const_sequence&&) = default;
        const_sequence& operator=(const_sequence&&) = default;

        const_sequence(sequence<T>&& x)
        :sequence<T>(std::move(x)) {}

        explicit operator bool() const {
            return not empty();
        }

        const T& operator[](size_t i) const {
            app_assert(i < size());
            return std::vector<T>::operator[](i);
        }

        using sequence<T>::capacity;
        using sequence<T>::data;
        using sequence<T>::empty;
        using sequence<T>::size;
        using sequence<T>::begin;
        using sequence<T>::end;
    };

} // namespace app::gpuc
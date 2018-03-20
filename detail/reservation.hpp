#pragma once
#include <cstddef>
#include "assert.hpp"

namespace app::detail {

    class reservation {
        void* const  _data      = nullptr;
        const size_t _max_size  = ~size_t(0);
        size_t       _alignment = alignof(std::max_align_t);
        size_t       _allocated = 0;

    public: // structors

        reservation() = default;

        reservation(decltype(nullptr)) {}

        reservation(void* data, size_t size)
        :_data(data),_max_size((app_assert(data or not size),size)) {
            while (not (size_t(_data) % (_alignment << 1))) {
                _alignment <<= 1;
            }
        }

        template<typename T, unsigned Size>
        reservation(T (&data)[Size]):reservation(data,Size) {}

        reservation(const memory& m)
        :reservation(m,m.size()) {}

        reservation(reservation&&) = default;

        reservation& operator=(reservation&& b) {
            if (this != &b) new(this) reservation(std::move(b));
            return *this;
        }

    public: // capacity

        explicit operator bool() const { return _data != nullptr; }

        size_t alignment() const { return _alignment; }

        size_t allocated() const { return _allocated; }

        void* data() const { return _data; }

        size_t max_size() const { return _max_size; }

        size_t size() const { return data() ? _max_size : _allocated; }

        size_t unallocated() const { return _max_size - _allocated; }

    public: // allocation

        template<typename T>
        T* allocate(size_t n = 1) {
            enum : size_t { alignment = alignof(T) };
            const size_t address = size_t(_data) + _allocated;
            if (const auto align = address % alignment) {
                allocate(align, 1);
            }
            const auto size = sizeof(T) * n;
            return (T*)allocate(size, alignment);
        }

        void* allocate(const size_t size, const size_t alignment) {
            app_assert(_allocated + size <= _max_size);
            if (_allocated == 0) {
                _alignment = std::max(_alignment, alignment);
            }
            void* const ptr = peek();
            app_assert(size_t(ptr) % alignment == 0);
            _allocated += size;
            return ptr;
        }

        void* allocate(const size_t size, const std::align_val_t alignment) {
            return allocate(size, size_t(alignment));
        }

    private: // utility

        void* peek() const {
            const size_t data = size_t(_data);
            const size_t size = unallocated();
            const size_t has_data_and_size = (data > 0) & (size > 0);
            const size_t offset = _allocated * has_data_and_size;
            const size_t address = data + offset;
            return (void*)address;
        }

    };

} // namespace app::detail
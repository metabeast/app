#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <new>
#include <type_traits>

namespace app::detail {

    template<typename U>
    struct fnv1a {
        // based on:
        // http://isthe.com/chongo/tech/comp/fnv/index.html

        using uint_type = U;

        enum : uint_type {
            basis =
                (sizeof(uint_type) == sizeof(uint32_t))
                ? uint_type(UINT32_C(2166136261))
                : uint_type(UINT64_C(14695981039346656037)),
            prime =
                (sizeof(uint_type) == sizeof(uint32_t))
                ? uint_type(UINT32_C(16777619))
                : uint_type(UINT64_C(1099511628211)),
        };

        const uint_type hash { basis };

        fnv1a() = default;

        fnv1a(uint_type basis)
        :hash(basis) {}

        fnv1a(const char* str)
        :hash(basis) { operator()(str); }

        fnv1a(const void* data, const size_t size)
        :hash(basis) { operator()(data,size); }

        fnv1a& operator()(const char* str) {
            return operator()(str,strlen(str));
        }

        fnv1a& operator()(const void* data, const size_t size) {
            uint_type hash = fnv1a::hash;
            const uint8_t* itr = (const uint8_t*)data;
            const uint8_t* const end = itr + size;
            for (; itr < end; ++itr) { hash ^= itr[0]; hash *= prime; }
            return *new(this) fnv1a(hash);
        }

        operator uint_type() const { return hash; }
    };

    using fnv1a32 = fnv1a<uint32_t>;
    using fnv1a64 = fnv1a<uint64_t>;

} // namespace app::detail
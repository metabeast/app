#pragma once
#include <memory>

namespace app::detail {

    template<typename T>
    struct unique_ptr : std::unique_ptr<T> {
        using std::unique_ptr<T>::unique_ptr;
        using std::unique_ptr<T>::operator=;
        unique_ptr& operator =(const unique_ptr&) = delete;
        unique_ptr& operator =(T* p) { reset(p); return *this; }
        operator T*() const { return std::unique_ptr<T>::get(); }
        unique_ptr<T> operator ~() { return { std::unique_ptr<T>::release() }; }
    };

    template<typename T>
    using captive = unique_ptr<T>;

    template<typename T>
    captive<T> capture(captive<T>&& p) {
        return std::move(p);
    }

    template<typename T>
    captive<T> capture(T* p) {
        return captive<T>(p);
    }

} // namespace app::detail
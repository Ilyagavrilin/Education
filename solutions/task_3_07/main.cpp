#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <utility>

template <class T>
class Vector {
    T* data_{nullptr};
    std::size_t cap_{0};
    std::size_t sz_{0};

    void grow_if_needed() {
        if (sz_ < cap_) return;
        std::size_t new_cap = cap_ ? cap_ + cap_/2 + 1 : 1;
        T* nd = static_cast<T*>(::operator new(sizeof(T) * new_cap));
        for (std::size_t i = 0; i < sz_; ++i) {
            std::construct_at(nd + i, std::move_if_noexcept(data_[i]));
            std::destroy_at(data_ + i);
        }
        ::operator delete(data_);
        data_ = nd;
        cap_ = new_cap;
    }

public:
    ~Vector() {
        clear();
        ::operator delete(data_);
    }

    bool empty() const noexcept { return sz_ == 0; }
    std::size_t size() const noexcept { return sz_; }
    std::size_t capacity() const noexcept { return cap_; }

    void push_back(const T& v) {
        grow_if_needed();
        std::construct_at(data_ + sz_, v);
        ++sz_;
    }
    void push_back(T&& v) {
        grow_if_needed();
        std::construct_at(data_ + sz_, std::move(v));
        ++sz_;
    }

    void clear() noexcept {
        for (std::size_t i = 0; i < sz_; ++i) std::destroy_at(data_ + i);
        sz_ = 0;
    }

    T& operator[](std::size_t i) noexcept { return data_[i]; }
    const T& operator[](std::size_t i) const noexcept { return data_[i]; }
};

int main() {
    Vector<int> v;
    assert(v.empty() && v.size()==0 && v.capacity()==0);
    for (int i = 0; i < 100; ++i) v.push_back(i);
    for (int i = 0; i < 100; ++i) assert(v[i]==i);
    assert(v.size()==100);
    auto cap = v.capacity();
    v.clear();
    assert(v.size()==0 && v.capacity()==cap && v.empty());
    for (int i = 0; i < 3; ++i) v.push_back(i*i);
    assert(v.size()==3 && v[2]==4);
    std::cout << "OK\n";
}

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

static void insertion_sort(std::vector<int>& v, std::size_t left, std::size_t right) {
    for (auto i = left + 1; i < right; ++i) {
        auto key = v[i];
        auto j = i;
        while (j > left && v[j - 1] > key) { v[j] = v[j - 1]; --j; }
        v[j] = key;
    }
}

constexpr std::size_t midpoint(std::size_t left, std::size_t right) noexcept {
    return left + (right - left) / 2;
}

std::size_t median_of_three(std::vector<int>& v, std::size_t a, std::size_t b, std::size_t c) {
    auto& x = v[a]; auto& y = v[b]; auto& z = v[c];
    if (x > y) std::swap(x, y);
    if (y > z) std::swap(y, z);
    if (x > y) std::swap(x, y);
    return b;
}

std::size_t hoare_partition(std::vector<int>& v, std::size_t left, std::size_t right) {
    auto mid = midpoint(left, right);
    auto pivot = v[median_of_three(v, left, mid, right - 1)];
    std::ptrdiff_t i = static_cast<std::ptrdiff_t>(left) - 1;
    std::ptrdiff_t j = static_cast<std::ptrdiff_t>(right);
    while (true) {
        do { ++i; } while (v[i] < pivot);
        do { --j; } while (v[j] > pivot);
        if (i >= j) return j + 1;
        std::swap(v[i], v[j]);
    }
}

void quick_split(std::vector<int>& v, std::size_t left, std::size_t right) {
    constexpr std::size_t cutoff = 16;
    while (right - left > cutoff) {
        auto m = hoare_partition(v, left, right);
        if (m - left < right - m) { quick_split(v, left, m); left = m; }
        else { quick_split(v, m, right); right = m; }
    }
    insertion_sort(v, left, right);
}

void quick_sort(std::vector<int>& v) {
    if (v.size() < 2) return;
    quick_split(v, 0, v.size());
}

int main() {
    std::vector<int> v(1'000);
    for (size_t i = 0; i < v.size(); ++i) v[i] = static_cast<int>(v.size() - i);
    quick_sort(v);
    assert(std::ranges::is_sorted(v));
    std::cout << "Validated good\n";
}

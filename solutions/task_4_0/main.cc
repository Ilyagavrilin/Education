#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>


// this is not good at all, but leave it like it is
template<typename T>
concept Sortable = std::movable<T> && std::totally_ordered<T>; 

template<Sortable T>
static void insertion_sort(std::vector<T>& v, std::size_t left, std::size_t right) {
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

template<Sortable T>
std::size_t median_of_three(std::vector<T>& v, std::size_t a, std::size_t b, std::size_t c) {
    auto& x = v[a]; auto& y = v[b]; auto& z = v[c];
    if (x > y) std::swap(x, y);
    if (y > z) std::swap(y, z);
    if (x > y) std::swap(x, y);
    return b;
}

template<Sortable T>
std::size_t hoare_partition(std::vector<T>& v, std::size_t left, std::size_t right) {
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

template<Sortable T>
void quick_split(std::vector<T>& v, std::size_t left, std::size_t right) {
    constexpr std::size_t cutoff = 16;
    while (right - left > cutoff) {
        auto m = hoare_partition(v, left, right);
        if (m - left < right - m) { quick_split(v, left, m); left = m; }
        else { quick_split(v, m, right); right = m; }
    }
    insertion_sort(v, left, right);
}

template<Sortable T>
void quick_sort(std::vector<T>& v) {
    if (v.size() < 2) return;
    quick_split(v, 0, v.size());
}

TEST(QuickSortTest, IntegersReversed) {
    std::vector<int> v(1000);
    for (size_t i = 0; i < v.size(); ++i) v[i] = static_cast<int>(v.size() - i);
    quick_sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSortTest, IntegersSorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    quick_sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSortTest, Doubles) {
    std::vector<double> v = {3.14, 2.71, 1.41, 0.5, 9.8, -1.5};
    quick_sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSortTest, Strings) {
    std::vector<std::string> v = {"zebra", "apple", "mango", "banana", "cherry"};
    quick_sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSortTest, Chars) {
    std::vector<char> v = {'z', 'a', 'm', 'b', 'c', 'A', 'Z'};
    quick_sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

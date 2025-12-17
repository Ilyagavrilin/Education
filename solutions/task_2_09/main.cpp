#include <cassert>
#include <iostream>
#include <numeric>

constexpr int gcd_recursive(int a, int b) noexcept {
    return b == 0 ? std::abs(a) : gcd_recursive(b, a % b);
}

constexpr int gcd_iterative(int a, int b) noexcept {
    a = std::abs(a); b = std::abs(b);
    while (b != 0) { int t = a % b; a = b; b = t; }
    return a;
}

constexpr int lcm_int(int a, int b) noexcept {
    if (a == 0 || b == 0) return 0;
    return std::abs(a / std::gcd(a, b) * b);
}

int main() {
    for (auto [a, b] : {std::pair{18,24}, {270,192}, {100,35}, {7,13}}) {
        assert(gcd_recursive(a,b) == std::gcd(a,b));
        assert(gcd_iterative(a,b) == std::gcd(a,b));
        assert(lcm_int(a,b) == std::lcm(a,b));
    }
    std::cout << "Validated good\n";
}

#include <array>
#include <cassert>
#include <cmath>
#include <print>
// use other algo cause it works better
consteval double compute_pi(double epsilon) {
    double sum = 0.0;
    double term = 1.0;
    int n = 0;
    
    while (std::abs(term) >= epsilon) {
        term = (n % 2 == 0 ? 1.0 : -1.0) / (2.0 * n + 1.0);
        sum += term;
        ++n;
    }
    
    return 4.0 * sum;
}

consteval double compute_e(double epsilon) {
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    
    while (term >= epsilon) {
        term /= n;
        sum += term;
        ++n;
    }
    
    return sum;
}

constexpr std::array epsilons = {1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6};

constexpr double pi_1e1 = compute_pi(1e-1);
constexpr double pi_1e2 = compute_pi(1e-2);
constexpr double pi_1e3 = compute_pi(1e-3);
constexpr double pi_1e4 = compute_pi(1e-4);
constexpr double pi_1e5 = compute_pi(1e-5);

constexpr double e_1e1 = compute_e(1e-1);
constexpr double e_1e2 = compute_e(1e-2);
constexpr double e_1e3 = compute_e(1e-3);
constexpr double e_1e4 = compute_e(1e-4);
constexpr double e_1e5 = compute_e(1e-5);

static_assert(pi_1e1 > 2.5 && pi_1e1 < 3.5);
static_assert(pi_1e2 > 3.0 && pi_1e2 < 3.3);
static_assert(pi_1e3 > 3.1 && pi_1e3 < 3.2);
static_assert(pi_1e4 > 3.13 && pi_1e4 < 3.15);
static_assert(pi_1e5 > 3.14 && pi_1e5 < 3.145);
// hits default depth of compile-time recursion
//static_assert(pi_1e6 > 3.141 && pi_1e6 < 3.143);

static_assert(e_1e1 > 2.5 && e_1e1 < 3.0);
static_assert(e_1e2 > 2.7 && e_1e2 < 2.8);
static_assert(e_1e3 > 2.71 && e_1e3 < 2.72);
static_assert(e_1e4 > 2.718 && e_1e4 < 2.719);
static_assert(e_1e5 > 2.7182 && e_1e5 < 2.7183);
// hits default depth of compile-time recursion
//static_assert(e_1e6 > 2.71828 && e_1e6 < 2.71829);

int main() {
    std::println("Values:");
    std::println("Pi (epsilon=1e-3): {}", pi_1e3);
    std::println("Pi (epsilon=1e-4): {}", pi_1e4);
    std::println("");
    std::println("e (epsilon=1e-1): {}", e_1e1);
    std::println("e (epsilon=1e-2): {}", e_1e2);
    std::println("");
}

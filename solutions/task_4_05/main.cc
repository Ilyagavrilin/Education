#include <cassert>
#include <limits>
#include <print>

template<int N>
struct Fibonacci {
    static_assert(N >= 0, "Fibonacci number index must be non-negative");
    
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
    
    static_assert(
        Fibonacci<N - 1>::value <= std::numeric_limits<int>::max() - Fibonacci<N - 2>::value,
        "Integer overflow detected in Fibonacci calculation"
    );
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

template<int N>
inline constexpr int fibonacci_v = Fibonacci<N>::value;

static_assert(fibonacci_v<0> == 0);
static_assert(fibonacci_v<1> == 1);
static_assert(fibonacci_v<2> == 1);
static_assert(fibonacci_v<3> == 2);
static_assert(fibonacci_v<4> == 3);
static_assert(fibonacci_v<25> == 75025);
static_assert(fibonacci_v<30> == 832040);
static_assert(fibonacci_v<45> == 1134903170);

int main() {
    std::println("Fibonacci(20) = {}", fibonacci_v<20>);
    std::println("Fibonacci(45) = {}", fibonacci_v<45>);
}

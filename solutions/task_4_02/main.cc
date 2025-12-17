#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <print>

template <std::floating_point T> constexpr T max_value(T value) {
  return value;
}

template <std::floating_point T, std::floating_point... Args>
constexpr T max_value(T first, Args... args) {
  T rest = max_value(args...);
  return first > rest ? first : rest;
}

template <std::floating_point T> constexpr T min_value(T value) {
  return value;
}

template <std::floating_point T, std::floating_point... Args>
constexpr T min_value(T first, Args... args) {
  T rest = min_value(args...);
  return first < rest ? first : rest;
}

template <std::floating_point... Args> constexpr double sum(Args... args) {
  return (args + ...);
}

template <std::floating_point... Args> constexpr double average(Args... args) {
  return sum(args...) / sizeof...(args);
}

consteval bool run_compile_time_tests() {
  static_assert(max_value(3.5, 1.2, 7.8, 2.1, 5.9) == 7.8);
  static_assert(min_value(3.5, 1.2, 7.8, 2.1, 5.9) == 1.2);
  static_assert(sum(3.5, 1.2, 7.8, 2.1, 5.9) == 20.5);
  static_assert(average(3.5, 1.2, 7.8, 2.1, 5.9) == 4.1);

  static_assert(max_value(-1.0, -5.0, -3.0) == -1.0);
  static_assert(min_value(-1.0, -5.0, -3.0) == -5.0);
  static_assert(sum(-1.0, -5.0, -3.0) == -9.0);
  static_assert(average(-1.0, -5.0, -3.0) == -3.0);

  return true;
}

static_assert(run_compile_time_tests());

int main() {
  // volatile here to force runtime execution
  volatile double runtime_max = max_value(2.5, 8.9, 3.1, 6.7);
  volatile double runtime_min = min_value(2.5, 8.9, 3.1, 6.7);
  volatile double runtime_sum = sum(2.5, 8.9, 3.1, 6.7);
  volatile double runtime_avg = average(2.5, 8.9, 3.1, 6.7);

  assert(std::abs(runtime_max - 8.9) < 1e-9);
  assert(std::abs(runtime_min - 2.5) < 1e-9);
  assert(std::abs(runtime_sum - 21.2) < 1e-9);
  assert(std::abs(runtime_avg - 5.3) < 1e-9);

  std::println("All tests passed");
}

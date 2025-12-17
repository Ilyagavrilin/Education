#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

template <typename... Ts> class Tuple {};

template <typename T, typename... Ts> class Tuple<T, Ts...> {
public:
  constexpr Tuple(T &&x, Ts &&...xs)
      : m_head(std::forward<T>(x)), m_tail(std::forward<Ts>(xs)...) {}

  template <std::size_t I> constexpr auto get() const {
    if constexpr (I > 0) {
      return m_tail.template get<I - 1>();
    } else {
      return m_head;
    }
  }

  constexpr std::size_t size() const { return 1 + sizeof...(Ts); }

private:
  T m_head;
  Tuple<Ts...> m_tail;
};

template <> class Tuple<> {
public:
  constexpr Tuple() = default;
  constexpr std::size_t size() const { return 0; }
};

constexpr Tuple<int, double, int> tuple1(1, 2.5, 3);
static_assert(tuple1.get<0>() == 1);
static_assert(tuple1.get<1>() == 2.5);
static_assert(tuple1.get<2>() == 3);
static_assert(tuple1.size() == 3);

constexpr Tuple<int> tuple2(42);
static_assert(tuple2.get<0>() == 42);
static_assert(tuple2.size() == 1);

constexpr Tuple<> tuple3;
static_assert(tuple3.size() == 0);

constexpr Tuple<int, int, int, int> tuple4(1, 2, 3, 4);
static_assert(tuple4.get<0>() == 1);
static_assert(tuple4.get<1>() == 2);
static_assert(tuple4.get<2>() == 3);
static_assert(tuple4.get<3>() == 4);
static_assert(tuple4.size() == 4);

int main() {
  Tuple<int, double, int> tuple(1, 2.0, 5);
  assert(tuple.get<0>() == 1);
  assert(tuple.get<1>() == 2.0);
  assert(tuple.get<2>() == 5);
  assert(tuple.size() == 3);

  constexpr Tuple<int, int> ct(10, 20);
  static_assert(ct.get<0>() == 10);
  static_assert(ct.get<1>() == 20);
  static_assert(ct.size() == 2);
}

#include <cassert>
#include <type_traits>

template <typename T> struct is_class {
private:
  template <typename U> static auto test(int U::*) -> std::true_type;

  template <typename> static auto test(...) -> std::false_type;

public:
  static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T> inline constexpr bool is_class_v = is_class<T>::value;

template <typename T> struct add_const {
  using type = const T;
};

template <typename T> using add_const_t = typename add_const<T>::type;

template <typename T> struct remove_const {
  using type = T;
};

template <typename T> struct remove_const<const T> {
  using type = T;
};

template <typename T> using remove_const_t = typename remove_const<T>::type;

template <typename T> struct remove_reference {
  using type = T;
};

template <typename T> struct remove_reference<T &> {
  using type = T;
};

template <typename T> struct remove_reference<T &&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T> struct remove_cv {
  using type = T;
};

template <typename T> struct remove_cv<const T> {
  using type = T;
};

template <typename T> struct remove_cv<volatile T> {
  using type = T;
};

template <typename T> struct remove_cv<const volatile T> {
  using type = T;
};

template <typename T> using remove_cv_t = typename remove_cv<T>::type;

template <typename T> struct decay {
private:
  using U = remove_reference_t<T>;

public:
  using type = remove_cv_t<U>;
};

template <typename T> using decay_t = typename decay<T>::type;

template <bool B, typename T, typename F> struct conditional {
  using type = T;
};

template <typename T, typename F> struct conditional<false, T, F> {
  using type = F;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

struct TestClass {
  int x;
};

static_assert(is_class_v<TestClass> == true);
static_assert(is_class_v<int> == false);

static_assert(std::is_same_v<add_const_t<int>, const int>);
static_assert(std::is_same_v<remove_const_t<const int>, int>);

static_assert(std::is_same_v<remove_reference_t<int &>, int>);
static_assert(std::is_same_v<remove_cv_t<const int>, int>);

static_assert(std::is_same_v<decay_t<const int &>, int>);

static_assert(std::is_same_v<conditional_t<true, int, double>, int>);
static_assert(std::is_same_v<conditional_t<false, int, double>, double>);

int main() {}

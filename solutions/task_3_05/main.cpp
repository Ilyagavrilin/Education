// 03_05_SeparateOverrides/main.cpp
#include <cassert>
#include <string>
#include <string_view>
#include <utility>

struct Entity_v1 {
    virtual ~Entity_v1() = default;
    virtual int test(int) const = 0;
};

struct Entity_v2 {
    virtual ~Entity_v2() = default;
    virtual int test(int) const = 0;
};

struct Adapter_v1 : virtual Entity_v1 {
    virtual int test_v1(int) const = 0;
    int test(int x) const override final { return test_v1(x); }
};

struct Adapter_v2 : virtual Entity_v2 {
    virtual int test_v2(int) const = 0;
    int test(int x) const override final { return test_v2(x); }
};

class Client final : public Adapter_v1, public Adapter_v2 {
public:
    int test_v1(int x) const override { return x * x; }
    int test_v2(int x) const override { int s = 0; for (int i = 1; i <= x; ++i) s += i; return s; }
};

int main() {
    Client c;
    const Entity_v1& i1 = c;
    const Entity_v2& i2 = c;
    assert(i1.test(5) == 25);
    assert(i2.test(5) == 15);
    assert(&i1 != &i2);
}

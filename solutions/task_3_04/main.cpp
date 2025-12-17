// 03_04_AttorneyTesting/main.cpp
#include <cassert>
#include <cctype>
#include <string>
#include <string_view>
#include <utility>

class Entity {
    int test_v1(int x) { return x * x; }
    int test_v2(std::string_view s) { int sum = 0; for (unsigned char ch : s) sum += std::toupper(ch); return sum; }
public:
    struct Attorney {
        static int call_test_v1(Entity& e, int x) { return e.test_v1(x); }
        static int call_test_v2(Entity& e, std::string_view s) { return e.test_v2(s); }
        friend class Tester_v1;
        friend class Tester_v2;
    };
    //friend class Tester_v1;
    //friend class Tester_v2;
public:
    Entity() = default;
};

class Tester_v1 {
public:
    static int run(Entity& e, int x) { return Entity::Attorney::call_test_v1(e, x); }
};

class Tester_v2 {
public:
    static int run(Entity& e, std::string_view s) { return Entity::Attorney::call_test_v2(e, s); }
};

int main() {
    Entity e;
    assert(Tester_v1::run(e, 5) == 25);
    assert(Tester_v1::run(e, -3) == 9);
    int a = Tester_v2::run(e, "abc");
    int b = Tester_v2::run(e, "ABC");
    assert(a == b);
}

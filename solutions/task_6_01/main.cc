#include "rational.hpp"
#include <cassert>
#include <cmath>
#include <sstream>

static bool equal(double x, double y, double eps = 1e-6) {
    return std::abs(x - y) < eps;
}

int main() {
    Rational x = 1, y(2, 1);

    assert(equal(static_cast<double>(x), 1));

    assert((x += y) == Rational(+3, 1));
    assert((x -= y) == Rational(+1, 1));
    assert((x *= y) == Rational(+2, 1));
    assert((x /= y) == Rational(+1, 1));

    assert((x++) == Rational(+1, 1));
    assert((x--) == Rational(+2, 1));
    assert((++y) == Rational(+3, 1));
    assert((--y) == Rational(+2, 1));

    assert((x + y) == Rational(+3, 1));
    assert((x - y) == Rational(-1, 1));
    assert((x * y) == Rational(+2, 1));
    assert((x / y) == Rational(+1, 2));

    assert((x += 1) == Rational(+2, 1));
    assert((x + 1) == Rational(+3, 1));
    assert((1 + y) == Rational(+3, 1));
    assert((1 + 1) == Rational(+2, 1));

    assert((x < y) == 0);
    assert((x > y) == 0);
    assert((x <= y) == 1);
    assert((x >= y) == 1);
    assert((x == y) == 1);
    assert((x != y) == 0);

    std::stringstream s1("1/2"), s2;
    s1 >> x;
    s2 << x;
    assert(s2.str() == s1.str());
}

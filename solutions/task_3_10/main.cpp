#include <cassert>
#include <cmath>
#include <compare>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>

class Rational {
public:
    Rational(int num = 0, int den = 1) : m_num(num), m_den(den) { reduce(); }
    explicit operator double() const { return 1.0 * m_num / m_den; }

    Rational& operator+=(Rational const& other) {
        auto l = std::lcm(m_den, other.m_den);
        m_num = m_num * (l / m_den) + other.m_num * (l / other.m_den);
        m_den = l;
        reduce();
        return *this;
    }
    Rational& operator-=(Rational const& other) { return *this += Rational(-other.m_num, other.m_den); }
    Rational& operator*=(Rational const& other) { m_num *= other.m_num; m_den *= other.m_den; reduce(); return *this; }
    Rational& operator/=(Rational const& other) { return *this *= Rational(other.m_den, other.m_num); }

    Rational operator++(int) { auto x = *this; *this += 1; return x; }
    Rational operator--(int) { auto x = *this; *this -= 1; return x; }
    Rational& operator++() { *this += 1; return *this; }
    Rational& operator--() { *this -= 1; return *this; }

    friend Rational operator+(Rational lhs, Rational const& rhs) { return lhs += rhs; }
    friend Rational operator-(Rational lhs, Rational const& rhs) { return lhs -= rhs; }
    friend Rational operator*(Rational lhs, Rational const& rhs) { return lhs *= rhs; }
    friend Rational operator/(Rational lhs, Rational const& rhs) { return lhs /= rhs; }

    friend bool operator==(Rational const& lhs, Rational const& rhs) {
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }

    friend std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs) {
        long long a = static_cast<long long>(lhs.m_num) * rhs.m_den;
        long long b = static_cast<long long>(rhs.m_num) * lhs.m_den;
        if (a < b) return std::strong_ordering::less;
        if (a > b) return std::strong_ordering::greater;
        return std::strong_ordering::equivalent;
    }

    friend std::istream& operator>>(std::istream& stream, Rational& r) {
        char slash{};
        stream >> r.m_num >> slash >> r.m_den;
        r.reduce();
        return stream;
    }
    friend std::ostream& operator<<(std::ostream& stream, Rational const& r) {
        return stream << r.m_num << '/' << r.m_den;
    }

private:
    void reduce() {
        if (m_den < 0) { m_num = -m_num; m_den = -m_den; }
        auto g = std::gcd(m_num, m_den);
        if (g) { m_num /= g; m_den /= g; }
    }

    int m_num{0}, m_den{1};
};

static bool equal(double x, double y, double eps = 1e-6) { return std::abs(x - y) < eps; }

int main() {
    Rational x = 1, y(2, 1);
    std::vector<int> v2(5);
    std::vector<int> v3{1,2,3,4,5};

    assert(equal(static_cast<double>(x), 1));

    assert((x += y) == Rational(+3, 1));
    assert((x -= y) == Rational(+1, 1));
    assert((x *= y) == Rational(+2, 1));
    assert((x /= y) == Rational(+1, 1));

    assert((x++  ) == Rational(+1, 1));
    assert((x--  ) == Rational(+2, 1));
    assert((++y  ) == Rational(+3, 1));
    assert((--y  ) == Rational(+2, 1));

    [[maybe_unused]] auto z = 0;

    assert((x +  y) == Rational(+3, 1));
    assert((x -  y) == Rational(-1, 1));
    assert((x *  y) == Rational(+2, 1));
    assert((x /  y) == Rational(+1, 2));

    assert((x += 1) == Rational(+2, 1));
    assert((x +  1) == Rational(+3, 1));
    assert((1 +  y) == Rational(+3, 1));
    assert((1 +  1) == Rational(+2, 1));

    assert((x <  y) == 0);
    assert((x >  y) == 0);
    assert((x <= y) == 1);
    assert((x >= y) == 1);
    assert((x == y) == 1);
    assert((x != y) == 0);

    std::stringstream s1("1/2"), s2;
    s1 >> x;
    s2 << x;
    assert(s2.str() == s1.str());
}

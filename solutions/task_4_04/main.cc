#include <cassert>
#include <cmath>
#include <compare>
#include <concepts>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>

template<std::integral T>
class Rational {
public:
    Rational(T num = 0, T den = 1) : m_num(num), m_den(den) { reduce(); }
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
        auto a = static_cast<long long>(lhs.m_num) * rhs.m_den;
        auto b = static_cast<long long>(rhs.m_num) * lhs.m_den;
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

    T m_num{0}, m_den{1};
};

static bool equal(double x, double y, double eps = 1e-6) { return std::abs(x - y) < eps; }

TEST(RationalTest, IntType) {
    Rational<int> x = 1, y(2, 1);
    EXPECT_TRUE(equal(static_cast<double>(x), 1));
    EXPECT_EQ((x += y), (Rational<int>(+3, 1)));
    EXPECT_EQ((x -= y), (Rational<int>(+1, 1)));
    EXPECT_EQ((x *= y), (Rational<int>(+2, 1)));
    EXPECT_EQ((x /= y), (Rational<int>(+1, 1)));
}

TEST(RationalTest, IncrementDecrement) {
    Rational<int> x = 1, y(2, 1);
    EXPECT_EQ((x++), (Rational<int>(+1, 1)));
    EXPECT_EQ((x--), (Rational<int>(+2, 1)));
    EXPECT_EQ((++y), (Rational<int>(+3, 1)));
    EXPECT_EQ((--y), (Rational<int>(+2, 1)));
}

TEST(RationalTest, BinaryOperators) {
    Rational<int> x = 1, y(2, 1);
    EXPECT_EQ((x + y), (Rational<int>(+3, 1)));
    EXPECT_EQ((x - y), (Rational<int>(-1, 1)));
    EXPECT_EQ((x * y), (Rational<int>(+2, 1)));
    EXPECT_EQ((x / y), (Rational<int>(+1, 2)));
}

TEST(RationalTest, MixedOperations) {
    Rational<int> x = 1, y(2, 1);
    EXPECT_EQ((x += 1), (Rational<int>(+2, 1)));
    EXPECT_EQ((x + 1), (Rational<int>(+3, 1)));
    EXPECT_EQ((1 + y), (Rational<int>(+3, 1)));
    EXPECT_EQ((1 + 1), (Rational<int>(+2, 1)));
}

TEST(RationalTest, Comparisons) {
    Rational<int> x(2, 1), y(2, 1);
    EXPECT_FALSE(x < y);
    EXPECT_FALSE(x > y);
    EXPECT_TRUE(x <= y);
    EXPECT_TRUE(x >= y);
    EXPECT_TRUE(x == y);
    EXPECT_FALSE(x != y);
}

TEST(RationalTest, IO) {
    Rational<int> x;
    std::stringstream s1("1/2"), s2;
    s1 >> x;
    s2 << x;
    EXPECT_EQ(s2.str(), "1/2");
}

TEST(RationalTest, LongType) {
    Rational<long> x(1000000, 1), y(2000000, 1);
    EXPECT_EQ((x + y), (Rational<long>(3000000, 1)));
    EXPECT_EQ((x * y), (Rational<long>(2000000000000, 1)));
}

TEST(RationalTest, LongLongType) {
    Rational<long long> x(1000000000, 1), y(2000000000, 1);
    EXPECT_EQ((x + y), (Rational<long long>(3000000000, 1)));
}

TEST(RationalTest, ShortType) {
    Rational<short> x(10, 1), y(20, 1);
    EXPECT_EQ((x + y), (Rational<short>(30, 1)));
    EXPECT_EQ((x * y), (Rational<short>(200, 1)));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

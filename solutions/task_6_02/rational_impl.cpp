module rational;

import std;

namespace math {

Rational::Rational(int num, int den) : m_num(num), m_den(den) { reduce(); }

Rational &Rational::operator+=(Rational const &other) {
  auto l = std::lcm(m_den, other.m_den);
  m_num = m_num * (l / m_den) + other.m_num * (l / other.m_den);
  m_den = l;
  reduce();
  return *this;
}

Rational &Rational::operator-=(Rational const &other) {
  return *this += Rational(-other.m_num, other.m_den);
}

Rational &Rational::operator*=(Rational const &other) {
  m_num *= other.m_num;
  m_den *= other.m_den;
  reduce();
  return *this;
}

Rational &Rational::operator/=(Rational const &other) {
  return *this *= Rational(other.m_den, other.m_num);
}

Rational Rational::operator++(int) {
  auto x = *this;
  *this += 1;
  return x;
}

Rational Rational::operator--(int) {
  auto x = *this;
  *this -= 1;
  return x;
}

std::strong_ordering operator<=>(Rational const &lhs, Rational const &rhs) {
  long long a = static_cast<long long>(lhs.m_num) * rhs.m_den;
  long long b = static_cast<long long>(rhs.m_num) * lhs.m_den;
  if (a < b)
    return std::strong_ordering::less;
  if (a > b)
    return std::strong_ordering::greater;
  return std::strong_ordering::equivalent;
}

std::istream &operator>>(std::istream &stream, Rational &r) {
  char slash{};
  stream >> r.m_num >> slash >> r.m_den;
  r.reduce();
  return stream;
}

std::ostream &operator<<(std::ostream &stream, Rational const &r) {
  return stream << r.m_num << '/' << r.m_den;
}

void Rational::reduce() {
  if (m_den < 0) {
    m_num = -m_num;
    m_den = -m_den;
  }
  auto g = std::gcd(m_num, m_den);
  if (g) {
    m_num /= g;
    m_den /= g;
  }
}

} // namespace math

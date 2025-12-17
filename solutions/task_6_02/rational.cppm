export module rational;

import std;

export namespace math {

class Rational {
public:
  Rational(int num = 0, int den = 1);
  explicit operator double() const { return 1.0 * m_num / m_den; }

  Rational &operator+=(Rational const &other);
  Rational &operator-=(Rational const &other);
  Rational &operator*=(Rational const &other);
  Rational &operator/=(Rational const &other);

  Rational operator++(int);
  Rational operator--(int);
  Rational &operator++() { return *this += 1; }
  Rational &operator--() { return *this -= 1; }

  friend Rational operator+(Rational lhs, Rational const &rhs) {
    return lhs += rhs;
  }
  friend Rational operator-(Rational lhs, Rational const &rhs) {
    return lhs -= rhs;
  }
  friend Rational operator*(Rational lhs, Rational const &rhs) {
    return lhs *= rhs;
  }
  friend Rational operator/(Rational lhs, Rational const &rhs) {
    return lhs /= rhs;
  }

  friend bool operator==(Rational const &lhs, Rational const &rhs) {
    return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
  }

  friend std::strong_ordering operator<=>(Rational const &lhs,
                                          Rational const &rhs);

  friend std::istream &operator>>(std::istream &stream, Rational &r);
  friend std::ostream &operator<<(std::ostream &stream, Rational const &r);

private:
  void reduce();

  int m_num{0}, m_den{1};
};

} // namespace math

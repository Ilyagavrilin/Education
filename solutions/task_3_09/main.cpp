#include <array>
#include <cassert>
#include <compare>
#include <cstdint>
#include <iostream>
#include <sstream> 

class IPv4 {
    std::uint8_t m_[4]{0,0,0,0};
public:
    IPv4() = default;
    IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) : m_{a,b,c,d} {}

    // Преобразования к/из 32-битного представления
    std::uint32_t to_u32() const noexcept {
        return (static_cast<std::uint32_t>(m_[0]) << 24) |
               (static_cast<std::uint32_t>(m_[1]) << 16) |
               (static_cast<std::uint32_t>(m_[2]) << 8 ) |
               (static_cast<std::uint32_t>(m_[3])      );
    }
    static IPv4 from_u32(std::uint32_t v) noexcept {
        return IPv4{
            static_cast<std::uint8_t>((v >> 24) & 0xFF),
            static_cast<std::uint8_t>((v >> 16) & 0xFF),
            static_cast<std::uint8_t>((v >>  8) & 0xFF),
            static_cast<std::uint8_t>((v      ) & 0xFF)
        };
    }

    // ++/-- (префиксные и постфиксные) с переполнением по модулю 2^32
    IPv4& operator++() noexcept { *this = from_u32(to_u32() + 1u); return *this; }
    IPv4  operator++(int) noexcept { IPv4 tmp = *this; ++(*this); return tmp; }
    IPv4& operator--() noexcept { *this = from_u32(to_u32() - 1u); return *this; }
    IPv4  operator--(int) noexcept { IPv4 tmp = *this; --(*this); return tmp; }

    // Сравнения: == и <=> (остальные операторы выведутся автоматически)
    friend bool operator==(IPv4 const& a, IPv4 const& b) noexcept {
        return a.m_[0]==b.m_[0] && a.m_[1]==b.m_[1] && a.m_[2]==b.m_[2] && a.m_[3]==b.m_[3];
    }
    friend std::strong_ordering operator<=>(IPv4 const& a, IPv4 const& b) noexcept {
        auto ua = a.to_u32(), ub = b.to_u32();
        if (ua < ub) return std::strong_ordering::less;
        if (ua > ub) return std::strong_ordering::greater;
        return std::strong_ordering::equivalent;
    }

    // Ввод/вывод в формате a.b.c.d
    friend std::istream& operator>>(std::istream& is, IPv4& ip) {
        int parts[4]; char dot;
        for (int i = 0; i < 4; ++i) {
            if (!(is >> parts[i])) { is.setstate(std::ios::failbit); return is; }
            if (parts[i] < 0 || parts[i] > 255) { is.setstate(std::ios::failbit); return is; }
            if (i < 3) {
                if (!(is >> dot) || dot != '.') { is.setstate(std::ios::failbit); return is; }
            }
        }
        ip.m_[0]=static_cast<std::uint8_t>(parts[0]);
        ip.m_[1]=static_cast<std::uint8_t>(parts[1]);
        ip.m_[2]=static_cast<std::uint8_t>(parts[2]);
        ip.m_[3]=static_cast<std::uint8_t>(parts[3]);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, IPv4 const& ip) {
        return os << static_cast<int>(ip.m_[0]) << '.'
                  << static_cast<int>(ip.m_[1]) << '.'
                  << static_cast<int>(ip.m_[2]) << '.'
                  << static_cast<int>(ip.m_[3]);
    }
};

int main() {
    // basic check
    IPv4 a(192,168,0,1);
    IPv4 b = IPv4::from_u32(a.to_u32());
    assert(a == b);

    // overflow
    IPv4 z(255,255,255,255);
    ++z;                       // -> 0.0.0.0
    assert(z == IPv4(0,0,0,0));
    z--;                       // -> 255.255.255.255
    assert(z == IPv4(255,255,255,255));

    // stringstream
    std::istringstream iss("192.168.0.1");
    IPv4 ip;
    iss >> ip;
    assert(ip == IPv4(192,168,0,1));

    std::ostringstream oss;
    oss << ip;
    assert(oss.str() == "192.168.0.1");

    // compare
    IPv4 x(10,0,0,1), y(10,0,0,2);
    assert(x < y);
    assert(y > x);
    assert((x <=> y) == std::strong_ordering::less);

    return 0;
}

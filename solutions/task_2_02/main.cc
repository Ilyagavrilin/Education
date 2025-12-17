#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

namespace {
    constexpr double epsilon = 1e-12;

    inline bool is_zero(double x) {
        return std::abs(x) <= epsilon;
    }
}

int main() {
    double a{}, b{}, c{};
    if (!(std::cin >> a >> b >> c)) {
        return 1;
    }

    std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1); // limit precision with some logical limit

    if (is_zero(a)) {
        if (is_zero(b)) {
            if (is_zero(c)) {
                std::cout << "Infinite solutions\n";
            } else {
                std::cout << "No real roots\n";
            }
            return 0;
        }

        double x = -c / b;
        std::cout << x << "\n";
        return 0;
    }

    const double D = b * b - 4.0 * a * c;

    if (D > epsilon) {
        const double sqrtD = std::sqrt(D);

        const double x1 = (-b - sqrtD) / (2.0 * a);
        const double x2 = (-b + sqrtD) / (2.0 * a);

        std::cout << x1 << "\n" << x2 << "\n";
    } else if (is_zero(D)) {
        const double x = -b / (2.0 * a);
        std::cout << x << "\n";
    } else {
        std::cout << "No real roots\n";
    }

    return 0;
}

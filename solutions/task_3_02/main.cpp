#include <cassert>
#include <cmath>
#include <iostream>
#include <numbers>
#include <stdexcept>

class Triangle {
    double a_, b_, c_;
public:
    Triangle(double a, double b, double c)
        : a_(a), b_(b), c_(c) {
        if (a_ <= 0 || b_ <= 0 || c_ <= 0 || a_+b_<=c_ || a_+c_<=b_ || b_+c_<=a_)
            throw std::invalid_argument("Invalid triangle");
    }
    double perimeter() const noexcept { return a_ + b_ + c_; }
    double area() const noexcept {
        double p = perimeter()/2.0;
        return std::sqrt(std::max(0.0, p*(p-a_)*(p-b_)*(p-c_)));
    }
};

class Square {
    double s_;
public:
    explicit Square(double s) : s_(s) { if (s_ <= 0) throw std::invalid_argument("Invalid square"); }
    double perimeter() const noexcept { return 4*s_; }
    double area() const noexcept { return s_*s_; }
};

class Circle {
    double r_;
public:
    explicit Circle(double r) : r_(r) { if (r_ <= 0) throw std::invalid_argument("Invalid circle"); }
    double perimeter() const noexcept { return 2*std::numbers::pi*r_; }
    double area() const noexcept { return std::numbers::pi*r_*r_; }
};

int main() {
    Triangle t(3,4,5); assert(t.area()==6 && t.perimeter()==12);
    Square s(2); assert(s.area()==4 && s.perimeter()==8);
    Circle c(3); assert(std::abs(c.area()-std::numbers::pi*9) < 1e-12);
    std::cout << "✅ Shapes validated successfully\n";
}

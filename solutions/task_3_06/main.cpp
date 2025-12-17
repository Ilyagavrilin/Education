// 03_06_ShapesWithInterface/main.cpp
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <numbers>
#include <stdexcept>
#include <utility>
#include <vector>

struct Shape {
    virtual ~Shape() = default;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
};

class Triangle : public Shape {
    double a_, b_, c_;
public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
        if (a_ <= 0 || b_ <= 0 || c_ <= 0 || a_ + b_ <= c_ || a_ + c_ <= b_ || b_ + c_ <= a_) throw std::invalid_argument("Triangle");
    }
    double perimeter() const override final { return a_ + b_ + c_; }
    double area() const override final {
        double p = perimeter() / 2.0;
        return std::sqrt(std::max(0.0, p * (p - a_) * (p - b_) * (p - c_)));
    }
};

class Square final : public Shape {
    double s_;
public:
    explicit Square(double s) : s_(s) { if (s_ <= 0) throw std::invalid_argument("Square"); }
    double perimeter() const override final { return 4 * s_; }
    double area() const override final { return s_ * s_; }
};

class Circle final : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) { if (r_ <= 0) throw std::invalid_argument("Circle"); }
    double perimeter() const override final { return 2 * std::numbers::pi * r_; }
    double area() const override final { return std::numbers::pi * r_ * r_; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Triangle>(3,4,5));
    shapes.emplace_back(std::make_unique<Square>(2));
    shapes.emplace_back(std::make_unique<Circle>(3));
    double total_p = 0.0, total_a = 0.0;
    for (const auto& s : shapes) { total_p += s->perimeter(); total_a += s->area(); }
    assert(std::abs(total_p - (12 + 8 + 2*std::numbers::pi*3)) < 1e-12);
    assert(std::abs(total_a - (6 + 4 + std::numbers::pi*9)) < 1e-12);
}

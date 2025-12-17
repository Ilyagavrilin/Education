#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

struct Rectangle {
    int x1{}, y1{}, x2{}, y2{};
    [[nodiscard]] int width() const noexcept { return std::max(0, x2 - x1); }
    [[nodiscard]] int height() const noexcept { return std::max(0, y2 - y1); }
    [[nodiscard]] int area() const noexcept { return width() * height(); }
};

Rectangle intersect_all(const std::vector<Rectangle>& rs) {
    if (rs.empty()) return {};
    int l = std::numeric_limits<int>::min() / 2;
    int t = std::numeric_limits<int>::min() / 2;
    int r = std::numeric_limits<int>::max() / 2;
    int b = std::numeric_limits<int>::max() / 2;
    for (auto& x : rs) { l = std::max(l, x.x1); t = std::max(t, x.y1); r = std::min(r, x.x2); b = std::min(b, x.y2); }
    return {l, t, r, b};
}

Rectangle bounding_box(const std::vector<Rectangle>& rs) {
    if (rs.empty()) return {};
    int l = std::numeric_limits<int>::max();
    int t = std::numeric_limits<int>::max();
    int r = std::numeric_limits<int>::min();
    int b = std::numeric_limits<int>::min();
    for (auto& x : rs) { l = std::min(l, x.x1); t = std::min(t, x.y1); r = std::max(r, x.x2); b = std::max(b, x.y2); }
    return {l, t, r, b};
}

int main() {
    std::vector<Rectangle> rs{{0,0,10,10},{2,2,8,8},{4,4,12,12}};
    auto inter = intersect_all(rs);
    assert(inter.area() == 16);
    auto box = bounding_box(rs);
    assert(box.x2 == 12 && box.y2 == 12);
    std::cout << "Validated good\n";
}

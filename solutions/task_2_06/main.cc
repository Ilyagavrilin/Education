#include <cmath>
#include <iostream>
#include <limits>
#include <ranges>
#include <span>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>

int main() {
    constexpr std::size_t N = 100;
    static double raw[N] = {};

    std::size_t count = 0;

    while (count < N && std::cin >> raw[count]) {
        ++count;
    }

    if (count == 0) {
        return 0;
    }

    std::span<double> data(raw, count);

    const auto [min_it, max_it] = std::ranges::minmax_element(data);
    const double min_val = *min_it;
    const double max_val = *max_it;

    const double sum = std::accumulate(data.begin(), data.end(), 0.0);
    const double mean = sum / static_cast<double>(count);

    const double sq_sum = std::transform_reduce(
        data.begin(), data.end(),
        0.0, std::plus<>(),
        [mean](double x) { return (x - mean) * (x - mean); }
    );

    const double stdev = std::sqrt(sq_sum / static_cast<double>(count));

    std::cout.precision(std::numeric_limits<double>::digits10 + 1);
    std::cout << "min: "   << min_val << '\n'
              << "max: "   << max_val << '\n'
              << "mean: "  << mean    << '\n'
              << "stdev: " << stdev   << '\n';

    return 0;
}

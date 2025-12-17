#include <cstddef>
#include <iostream>
#include <vector>
#include <limits>

// Compute Collatz length for n using a memoization vector.
// Length counts number of terms until reaching 1, inclusive (len(1) == 1).
static std::size_t collatz_length(unsigned long long n, std::vector<std::size_t>& memo) {
    // Ensure memo has at least entries for indices [0..n]
    auto ensure_size = [&](unsigned long long idx) {
        if (idx >= memo.size()) {
            // grow to idx+1 (safe for this task range 1..100; peaks are modest)
            memo.resize(static_cast<std::size_t>(idx + 1), 0);
        }
    };

    // Walk forward until we find a cached value
    std::vector<unsigned long long> path;
    unsigned long long cur = n;

    while (true) {
        if (cur == 1ULL) {
            // Base: len(1) = 1
            ensure_size(1ULL);
            if (memo[1] == 0) memo[1] = 1;
            break;
        }
        if (cur < memo.size() && memo[cur] != 0) {
            // Found cached length
            break;
        }
        path.push_back(cur);
        if ((cur & 1ULL) == 0ULL) {
            cur /= 2ULL;
        } else {
            // 3n + 1 (fits safely for starts <= 100 for this task)
            cur = 3ULL * cur + 1ULL;
        }
        // make sure memo can hold 'cur' if needed later
        ensure_size(cur);
    }

    // Starting length from where we stopped
    std::size_t known_len = (cur < memo.size() && memo[cur] != 0) ? memo[cur]
                           : (cur == 1ULL ? memo[1] : 0);

    // Propagate back and fill memo
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        unsigned long long v = *it;
        ensure_size(v);
        // Each previous element adds one term
        memo[v] = known_len + 1;
        known_len = memo[v];
    }

    ensure_size(n);
    return memo[n];
}

int main() {
    // Memoization vector: index is the Collatz value, value is length (size_t).
    // memo[1] = 1, others 0 (unknown). We start small and grow as needed.
    std::vector<std::size_t> memo(2, 0);
    memo[1] = 1;

    std::size_t best_len = 0;
    unsigned long long best_start = 1;

    for (unsigned long long start = 1; start <= 100; ++start) {
        std::size_t len = collatz_length(start, memo);
        if (len > best_len) {
            best_len = len;
            best_start = start;
        }
    }

    // Print: maximum length and the starting value that gives it
    std::cout << "max_length: " << best_len << '\n'
              << "start: "      << best_start << '\n';

    return 0;
}

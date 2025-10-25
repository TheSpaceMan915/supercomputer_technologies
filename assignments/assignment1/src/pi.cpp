#include "assignment1/pi.h"

namespace assignment1 {

double approximate_pi(int n)
{
    if (n <= 0) {
        return 0.0;
    }
    const double inv_n = 1.0 / static_cast<double>(n);
    double sum = 0.0;
    for (int i = 1; i <= n; ++i) {
        const double x = (static_cast<double>(i) - 0.5) * inv_n;
        sum += 4.0 / (1.0 + x * x);
    }
    return sum * inv_n;
}

} // namespace assignment1

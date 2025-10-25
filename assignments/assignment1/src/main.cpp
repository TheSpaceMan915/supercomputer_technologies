#ifdef _WIN32
#  ifndef _USE_MATH_DEFINES
#    define _USE_MATH_DEFINES
#  endif
#endif

#include <cmath>
#ifndef M_PI
#  define M_PI 3.14159265358979323846
#endif

#include <cstdlib>
#include <cerrno>
#include <climits>
#include <ctime>
#include <sstream>
#include <string>
#include "assignment1/pi.h"
#include "assignment1/logger.h"

using assignment1::approximate_pi;
using assignment1::log_error;
using assignment1::log_info;

static bool parse_positive_int(const char* s, int& out)
{
    if (!s || *s == '\0') return false;
    errno = 0;
    char* endp = 0;
    long v = std::strtol(s, &endp, 10);
    if (errno == ERANGE) return false;
    if (endp == s || *endp != '\0') return false;
    if (v <= 0 || v > INT_MAX) return false;
    out = static_cast<int>(v);
    return true;
}

int main(int argc, char** argv)
{
    log_info("assignment1 start");

    if (argc != 2) {
        log_error("Usage: assignment1 <n>  (n must be a positive integer)");
        return 1;
    }

    int n = 0;
    if (!parse_positive_int(argv[1], n)) {
        log_error("Invalid n. Please provide a positive integer within range.");
        return 1;
    }

    const int MAX_N = 1000000000;
    if (n > MAX_N) {
        log_error("n is too large for a reasonable run. Try <= 1e9.");
        return 1;
    }

    {
        std::ostringstream oss;
        oss << "Parsed n = " << n;
        log_info(oss.str());
    }

    const std::clock_t t0 = std::clock();
    const double pi_est = approximate_pi(n);
    const std::clock_t t1 = std::clock();

    const double abs_err = (pi_est > M_PI) ? (pi_est - M_PI) : (M_PI - pi_est);
    const double secs = static_cast<double>(t1 - t0) / static_cast<double>(CLOCKS_PER_SEC);

    {
        std::ostringstream oss;
        oss.setf(std::ios::fixed);
        oss.precision(12);
        oss << "pi_est = " << pi_est;
        log_info(oss.str());
    }
    {
        std::ostringstream oss;
        oss.setf(std::ios::fixed);
        oss.precision(12);
        oss << "abs error vs M_PI = " << abs_err;
        log_info(oss.str());
    }
    {
        std::ostringstream oss;
        oss.setf(std::ios::fixed);
        oss.precision(3);
        oss << "elapsed = " << secs << " s";
        log_info(oss.str());
    }

    log_info("assignment1 done");
    return 0;
}

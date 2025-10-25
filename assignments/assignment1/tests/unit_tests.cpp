#include "assignment1/pi.h"

extern "C" {
#include "vendor/unity/unity.h"
}

#ifdef _WIN32
#  ifndef _USE_MATH_DEFINES
#    define _USE_MATH_DEFINES
#  endif
#endif
#include <cmath>
#ifndef M_PI
#  define M_PI 3.14159265358979323846
#endif

static void test_midpoint_rule_converges(void)
{
    const int n = 100000;
    const double approx = assignment1::approximate_pi(n);
    const double err = (approx > M_PI) ? (approx - M_PI) : (M_PI - approx);
    TEST_ASSERT_TRUE(err < 1e-5);
}

int main(void)
{
    UnityBegin("assignment1");
    RUN_TEST(test_midpoint_rule_converges);
    return UnityEnd();
}

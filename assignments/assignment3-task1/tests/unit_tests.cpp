#include "assignment3_task1/pi.h"
extern "C" {
#include "vendor/unity/unity.h"
    }
#ifdef _MSC_VER
#  ifndef _USE_MATH_DEFINES
#    define _USE_MATH_DEFINES
#  endif
#endif
#include <cmath>
#ifndef M_PI
#  define M_PI 3.14159265358979323846
#endif
static void test_parallel_accuracy_small_n(void){ const int n=1000; const double p=assignment3_task1::approximate_pi_parallel(n); const double e=(p>M_PI)?(p-M_PI):(M_PI-p); TEST_ASSERT_TRUE(e<1e-4); }
static void test_serial_parallel_match(void){ const int n=10000; const double ps=assignment3_task1::approximate_pi_serial(n); const double pp=assignment3_task1::approximate_pi_parallel(n); TEST_ASSERT_DOUBLE_WITHIN(1e-12, ps, pp); }
static void test_error_monotonicity(void){ const int n1=2000, n2=4000; const double p1=assignment3_task1::approximate_pi_parallel(n1); const double p2=assignment3_task1::approximate_pi_parallel(n2); const double e1=(p1>M_PI)?(p1-M_PI):(M_PI-p1); const double e2=(p2>M_PI)?(p2-M_PI):(M_PI-p2); TEST_ASSERT_TRUE(e2<=e1); }
int main(void){ UnityBegin("assignment3-task1"); RUN_TEST(test_parallel_accuracy_small_n); RUN_TEST(test_serial_parallel_match); RUN_TEST(test_error_monotonicity); return UnityEnd(); }

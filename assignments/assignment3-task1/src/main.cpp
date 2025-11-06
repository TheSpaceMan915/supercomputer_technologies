#ifdef _MSC_VER
#  ifndef _USE_MATH_DEFINES
#    define _USE_MATH_DEFINES
#  endif
#endif
#include <cmath>
#ifndef M_PI
#  define M_PI 3.14159265358979323846
#endif
#include "assignment3_task1/pi.h"
#include "assignment3_task1/logger.h"
#ifdef _OPENMP
#  include <omp.h>
#endif
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <ctime>
#include <sstream>
#include <string>
#include <iostream>
using assignment3_task1::approximate_pi_parallel; using assignment3_task1::log_error; using assignment3_task1::log_info;
static void usage(){ std::cerr << "Usage: assignment3-task1 <n>" << std::endl; }
static bool parse_positive_int(const char* s, int& out){ if(!s||*s=='\0') return false; errno=0; char* e=0; long v=strtol(s,&e,10); if(errno==ERANGE) return false; if(e==s||*e!='\0') return false; if(v<=0||v>INT_MAX) return false; out=(int)v; return true; }
static double wall_ms_now()
{
#ifdef _OPENMP
  return omp_get_wtime()*1000.0;
#else
  const clock_t c=clock(); return 1000.0*(double)c/(double)CLOCKS_PER_SEC;
#endif
}
int main(int argc,char** argv) {
  if(argc!=2){ log_error("invalid arguments"); usage(); return 1; }
  int n=0; if(!parse_positive_int(argv[1], n)){ std::ostringstream oss; oss << "invalid n: \"" << argv[1] << "\""; log_error(oss.str()); usage(); return 1; }
  if(n>2000000000L){ log_error("n is unreasonably large; choose a smaller value (<= 2e9)"); return 1; }
#ifdef _OPENMP
  const int threads = omp_get_max_threads();
#else
  const int threads = 1;
#endif
  log_info("assignment3-task1 start"); { std::ostringstream oss; oss << "n=" << n << " threads=" << threads; log_info(oss.str()); }
  const double t0 = wall_ms_now();
  const double pi = approximate_pi_parallel(n);
  const double t1 = wall_ms_now();
  const double err = (pi > M_PI) ? (pi - M_PI) : (M_PI - pi);
  const long elapsed_ms = (long)(t1 - t0 + 0.5);
  { std::ostringstream oss; oss.setf(std::ios::fixed); oss.precision(8); oss << "pi=" << pi; std::ostringstream e; e.setf(std::ios::scientific); e.precision(6); e << err; std::ostringstream out; out << oss.str() << " error=" << e.str() << " elapsed_ms=" << elapsed_ms; log_info(out.str()); }
  log_info("assignment3-task1 done");
  return 0;
}

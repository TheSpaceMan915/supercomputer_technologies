#include "assignment3_task1/pi.h"
#ifdef _OPENMP
#  include <omp.h>
#endif
namespace assignment3_task1 {
double approximate_pi_serial(int n){ if(n<=0) return 0.0; const double w=1.0/(double)n; double sum=0.0; for(int i=0;i<n;++i){ const double x=((double)i+0.5)*w; sum+=4.0/(1.0+x*x);} return w*sum; }
double approximate_pi_parallel(int n){
  if(n<=0) return 0.0;
  const double w=1.0/(double)n;
#ifndef _OPENMP
  return approximate_pi_serial(n);
#else
  double sum=0.0;
  #pragma omp parallel for reduction(+:sum) schedule(static)
  for(int i=0;i<n;++i){ const double x=((double)i+0.5)*w; sum+=4.0/(1.0+x*x); }
  return w*sum;
#endif
}
}

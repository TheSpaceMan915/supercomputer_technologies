#include "assignment3_task2/matrix.h"

#ifdef _OPENMP
#include <omp.h>
#endif

namespace assignment3_task2
{
    static inline int idx(int N, int i, int j)
    {
        return i * N + j;
    }

    void init_A(std::vector<double>& A, int N)
    {
        A.resize(N * N);
        for (int i = 0; i < N; ++i)
        {
            const double base = static_cast<double>(i + 1);
            for (int j = 0; j < N; ++j)
            {
                A[idx(N, i, j)] = base;
            }
        }
    }

    void init_B(std::vector<double>& B, int N)
    {
        B.resize(N * N);
        for (int j = 0; j < N; ++j)
        {
            const double col = 1.0 / static_cast<double>(j + 1);
            for (int i = 0; i < N; ++i)
            {
                B[idx(N, i, j)] = col;
            }
        }
    }

    void multiply_serial(const std::vector<double>& A,
                         const std::vector<double>& B,
                         std::vector<double>& C,
                         int N)
    {
        C.assign(N * N, 0.0);

        for (int i = 0; i < N; ++i)
        {
            const int row = i * N;
            for (int j = 0; j < N; ++j)
            {
                double sum = 0.0;
                for (int k = 0; k < N; ++k)
                {
                    sum += A[row + k] * B[k * N + j];
                }
                C[row + j] = sum;
            }
        }
    }

    void multiply_parallel(const std::vector<double>& A,
                           const std::vector<double>& B,
                           std::vector<double>& C,
                           int N)
    {
        C.assign(N * N, 0.0);

#if defined(_OPENMP)
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < N; ++i)
        {
            const int row = i * N;
            for (int j = 0; j < N; ++j)
            {
                double sum = 0.0;
                for (int k = 0; k < N; ++k)
                {
                    sum += A[row + k] * B[k * N + j];
                }
                C[row + j] = sum;
            }
        }
#else
        multiply_serial(A, B, C, N);
#endif
    }
}

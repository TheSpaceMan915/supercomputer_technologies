#ifndef ASSIGNMENT3_TASK2_MATRIX_H
#define ASSIGNMENT3_TASK2_MATRIX_H

#include <vector>

namespace assignment3_task2
{
    void init_A(std::vector<double>& A, int N);
    void init_B(std::vector<double>& B, int N);

    void multiply_serial(const std::vector<double>& A,
                         const std::vector<double>& B,
                         std::vector<double>& C,
                         int N);

    void multiply_parallel(const std::vector<double>& A,
                           const std::vector<double>& B,
                           std::vector<double>& C,
                           int N);
}

#endif

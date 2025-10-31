#ifndef ASSIGNMENT2_MATRIX_H
#define ASSIGNMENT2_MATRIX_H

#include <vector>

namespace assignment2 {

struct Matrix {
  int n;
  std::vector<double> data;
  explicit Matrix(int size);
  double& at(int i, int j);
  const double& at(int i, int j) const;
};

void initA(Matrix& A);
void initB(Matrix& B);
void multiply(const Matrix& A, const Matrix& B, Matrix& C);

} // namespace assignment2

#endif // ASSIGNMENT2_MATRIX_H

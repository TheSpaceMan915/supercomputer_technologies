#include "assignment2/matrix.h"
#include <stdexcept>

namespace assignment2 {

Matrix::Matrix(int size) : n(size), data()
{
  if (n <= 0) throw std::invalid_argument("Matrix size must be > 0");
  data.assign(static_cast<std::vector<double>::size_type>(n) *
              static_cast<std::vector<double>::size_type>(n), 0.0);
}

double& Matrix::at(int i, int j)
{
  return data[static_cast<std::vector<double>::size_type>(i * n + j)];
}

const double& Matrix::at(int i, int j) const
{
  return data[static_cast<std::vector<double>::size_type>(i * n + j)];
}

void initA(Matrix& A)
{
  const int N = A.n;
  for (int i = 0; i < N; ++i) {
    const double v = static_cast<double>(i + 1);
    for (int j = 0; j < N; ++j) {
      A.at(i, j) = v;
    }
  }
}

void initB(Matrix& B)
{
  const int N = B.n;
  for (int j = 0; j < N; ++j) {
    const double v = 1.0 / static_cast<double>(j + 1);
    for (int i = 0; i < N; ++i) {
      B.at(i, j) = v;
    }
  }
}

void multiply(const Matrix& A, const Matrix& B, Matrix& C)
{
  const int N = A.n;
  if (B.n != N || C.n != N) throw std::invalid_argument("Dimension mismatch");
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      double acc = 0.0;
      for (int k = 0; k < N; ++k) {
        acc += A.at(i, k) * B.at(k, j);
      }
      C.at(i, j) = acc;
    }
  }
}

} // namespace assignment2

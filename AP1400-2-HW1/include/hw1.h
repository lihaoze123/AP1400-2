#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include <algorithm>

using size_t = __SIZE_TYPE__;
using Matrix = std::vector<std::vector<double>>;

constexpr double _EPS = 1e-6;

namespace algebra {
    // Create a `n x m` matrix with all elements equals to zero.
    Matrix zeros(size_t n, size_t m);
    
    // Create a `n x m` matrix with all elements equals to one.
    Matrix ones(size_t n, size_t m);

    // Create a `n x m` matrix with all elements a random number between min and max.
    Matrix random(size_t n, size_t m, double min, double max);

    // Display the matrix in a beautiful way.
    void show(const Matrix& matrix);

    // Multiply the `matrix` into the constant scalar `c`
    Matrix multiply(const Matrix& matrix, double c);

    // Multiply the `matrix1` into `matrix2`
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);

    Matrix sum(const Matrix& matrix, double c);
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);
    Matrix transpose(const Matrix& matrix);
    Matrix minor(const Matrix& matrix, size_t n, size_t m);
    double determinant(const Matrix& matrix);
    Matrix inverse(const Matrix& matrix);
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);
    Matrix upper_triangular(const Matrix& matrix);
}

#endif //AP_HW1_H

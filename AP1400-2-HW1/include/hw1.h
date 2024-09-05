#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <iostream>
#include <functional>
#include <random>
#include <iostream>
#include <iomanip>
#include <algorithm>

using size_t = __SIZE_TYPE__;

constexpr double _EPS = 1e-6;

class Matrix {
private:
    std::vector<std::vector<double>> _data;

public:
    Matrix () = default;
    Matrix (size_t n, size_t m) : _data(n, std::vector<double>(m)) {}
    Matrix (size_t n, size_t m, double c) : _data(n, std::vector<double>(m, c)) {}

    Matrix (size_t n, size_t m, std::function<double()> f);

    Matrix (const std::vector<std::vector<double>>& data) : _data(data) {}
    Matrix (std::initializer_list<std::vector<double>> l) : _data(l) {}

    ~Matrix() = default;

    size_t size() const;
    bool empty() const;
    size_t innerSize() const;

    void show() const;

    std::vector<double>& operator[] (size_t index);
    const std::vector<double>& operator[] (size_t index) const;

    class Iterator {
    private:
        Matrix& matrix;
        size_t row;

    public:
        Iterator(Matrix& m, size_t r) : matrix(m), row(r) {}

        std::vector<double>& operator* ();
        Iterator& operator++ ();
        Iterator operator++ (int);
        bool operator!= (const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();

    const Iterator begin() const;
    const Iterator end() const;
};

std::ostream& operator<< (std::ostream& os, const Matrix& rhs);

namespace algebra {
    // Create a `n x m` matrix with all elements equals to zero.
    Matrix zeros(size_t n, size_t m);
    
    // Create a `n x m` matrix with all elements equals to one.
    Matrix ones(size_t n, size_t m);

    // Create a `n x m` matrix with all elements a random number between min and max.
    Matrix random(size_t n, size_t m, double min, double max);

    // Display the matrix in a beautiful way.
    void show(const Matrix& matrix);

    // Multiply the `matrix` into the constant scalar `c`.
    Matrix multiply(const Matrix& matrix, double c);

    // Multiply the `matrix1` into `matrix2`.
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);

    // Add the constant number `c` to every elements of `matrix`.
    Matrix sum(const Matrix& matrix, double c);

    // Add 2 matrices to each other.
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

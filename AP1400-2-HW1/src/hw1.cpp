#include "hw1.h"

namespace algebra {
Matrix zeros(size_t n, size_t m) {
    Matrix res(n, m);
    return res;
}

Matrix ones(size_t n, size_t m) {
    Matrix res(n, m, 1);
    return res;
}

Matrix random(size_t n, size_t m, double min, double max) {
    if (min > max) 
        throw std::logic_error("min is bigger than max");

    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max - _EPS);

    Matrix res(n, m, std::bind(distrib, gen));

    return res;
}

void show(const Matrix& matrix) {
    matrix.show();
}

Matrix multiply(const Matrix& matrix, double c) {
    Matrix res = matrix;

    for (auto& x : res) 
        for (auto& y : x) 
             y *= c;

    return res;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
    size_t n1 = matrix1.size(), 
           n2 = matrix2.size();

    if (n1 == 0 || n2 == 0) 
        return Matrix();

    size_t m1 = matrix1.innerSize(),
           m2 = matrix2.innerSize();

    if (m1 != n2) 
        throw std::logic_error("Matrix not matched!");

    auto res = zeros(n1, m2);

    for (size_t i = 0; i < n1; ++ i) 
        for (size_t j = 0; j < m2; ++ j) 
            for (size_t k = 0; k < m1; ++ k) 
                res[i][j] += matrix1[i][k] * matrix2[k][j];

    return res;
}

Matrix sum(const Matrix& matrix, double c) {
    Matrix res(matrix);

    for (auto &x : res) 
        for (auto &y : x)
            y += c;

    return res;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1.innerSize() != matrix2.innerSize())
        throw std::logic_error("Matrix not matched!");

    size_t n = matrix1.size(), m = matrix1.innerSize();

    Matrix res(matrix1);
    
    for (size_t i = 0; i < n; ++ i)
        for (size_t j = 0; j < m; ++ j)
            res[i][j] +=  matrix2[i][j];

    return res;
}

Matrix transpose(const Matrix& matrix) {
    return matrix.transpose();
}

Matrix minor(const Matrix &matrix, size_t n, size_t m) {
    return matrix.minor(n, m);
}

double determinant(const Matrix &matrix) {
    return matrix.determinant();
}

Matrix inverse(const Matrix &matrix) {
    return matrix.inv();
}

Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis) {
    if (matrix1.empty() && matrix2.empty())
        return Matrix();

    size_t n1 = matrix1.size(), n2 = matrix2.size(),
           m1 = matrix1.innerSize(), m2 = matrix2.innerSize();

    if (axis) {
        if (n1 != n2)
            throw std::logic_error("Matrix not matched!");

        Matrix res(matrix1);
        for (size_t i = 0; i < n1; ++ i)
            res[i].insert(res[i].end(), matrix2[i].begin(), matrix2[i].end());

        return res;
    } else {
        if (m1 != m2)
            throw std::logic_error("Matrix not matched!");

        Matrix res(n1 + n2, 0);

        for (size_t i = 0; i < n1; ++ i)
            res[i] = matrix1[i];
        for (size_t i = 0; i < n2; ++ i)
            res[i + n1] = matrix2[i];

        return res;
    }

    throw std::logic_error("Not a valid axis value!");
}

Matrix ero_swap(const Matrix &matrix, size_t r1, size_t r2) {
    Matrix res(matrix);

    auto swap = std::move(res[r1]);
    res[r1] = std::move(res[r2]);
    res[r2] = std::move(swap);

    return res;
}

Matrix ero_multiply(const Matrix &matrix, size_t r, double c) {
    Matrix res(matrix);

    for (auto &x : res[r])
        x *= c;

    return res;
}

Matrix ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2) {
    size_t m = matrix.innerSize();

    Matrix res(matrix);

    for (size_t i = 0; i < m; ++ i)
        res[r2][i] += res[r1][i] * c;

    return res;
}

Matrix upper_triangular(const Matrix &matrix) {
    return matrix.upper_triangular();
}

};

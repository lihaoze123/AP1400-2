#include "hw1.h"

size_t Matrix::size() const {
    return _data.size();
}

bool Matrix::empty() const {
    return _data.empty();
}

std::ostream& operator<< (std::ostream& os, const Matrix& rhs) {
    os << std::fixed << std::setprecision(3);

    for (const auto& x : rhs) {
        for (const auto& y : x) 
            os << std::setw(8) << y;
        os << '\n';
    }

    return os;
}

void Matrix::show() const {
    std::cout << *this;
}

std::vector<double>& Matrix::operator[] (size_t index) {
    return _data[index];
}

const std::vector<double>& Matrix::operator[] (size_t index) const {
    return _data[index];
}

std::vector<double>& Matrix::Iterator::operator* () {
    return matrix[row];
}

Matrix::Iterator& Matrix::Iterator::operator++ () {
    ++ row;
    return *this;
}

Matrix::Iterator Matrix::Iterator::operator++ (int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool Matrix::Iterator::operator!= (const Iterator& other) const {
    return row != other.row;
}

Matrix::Iterator Matrix::begin() {
    return Iterator(*this, 0);
}

Matrix::Iterator Matrix::end() {
    return Iterator(*this, size());
}

const Matrix::Iterator Matrix::begin() const {
    return Iterator(const_cast<Matrix&>(*this), 0);
}

const Matrix::Iterator Matrix::end() const {
    return Iterator(const_cast<Matrix&>(*this), size());
}

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
    if (min > max) {
        throw std::logic_error("min is bigger than max");
    }

    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max - _EPS);

    Matrix res(n, m);

    for (auto& x : res) 
        for (auto& y : x) 
            y = distrib(gen);

    return res;
}

void show(const Matrix& matrix) {
    matrix.show();
}

Matrix multiply(const Matrix& matrix, double c) {
    Matrix res = matrix;

    for (auto& x : res) {
        std::transform(x.begin(), x.end(), x.begin(), [c] (const double& y) {
            return y * c;
        });
    }

    return res;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
    size_t n1 = matrix1.size(),
           n2 = matrix2.size();

    if (n1 == 0 || n2 == 0) {
        return Matrix();
    }

    int m1 = matrix1[0].size(),
        m2 = matrix2[0].size();

    if (m1 != n2) {
        throw std::logic_error("matrix not matched");
    }

    auto res = zeros(n1, m2);

    for (size_t i = 0; i < n1; ++ i) 
        for (size_t j = 0; j < m2; ++ j) 
            for (size_t k = 0; k < m1; ++ k) 
                res[i][j] += matrix1[i][k] * matrix2[k][j];

    return res;
}
};

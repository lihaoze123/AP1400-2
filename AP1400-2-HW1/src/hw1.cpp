#include "hw1.h"

namespace algebra {
Matrix zeros(size_t n, size_t m) {
    Matrix res(n, std::vector<double>(m));
    return res;
}

Matrix ones(size_t n, size_t m) {
    Matrix res(n, std::vector<double>(m, 1));
    return res;
}

Matrix random(size_t n, size_t m, double min, double max) {
    if (min > max) {
        throw std::logic_error("min is bigger than max");
    }

    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max - _EPS);

    Matrix res(n, std::vector<double>(m));

    for (auto& x : res) 
        for (auto& y : x) 
            y = distrib(gen);

    return res;
}

void show(const Matrix &matrix) {
    std::cout << std::fixed << std::setprecision(3);

    for (const auto& x : matrix) {
        for (const auto& y : x) {
            std::cout << std::setw(8) << y;
        }
        std::cout << '\n';
    }
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
    size_t n1 = matrix1.size(), m1,
           n2 = matrix2.size(), m2;

    Matrix res;

    if (n1 == 0 || n2 == 0) {
        return res;
    }

    m1 = matrix1[0].size();
    m2 = matrix2[0].size();

    if (m1 != n2) {
        throw std::logic_error("matrix not matched");
    }

    res = zeros(n1, m2);

    for (size_t i = 0; i < n1; ++ i) 
        for (size_t j = 0; j < m2; ++ j) 
            for (size_t k = 0; k < m1; ++ k) 
                res[i][j] += matrix1[i][k] * matrix2[k][j];

    return res;
}
};

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
};

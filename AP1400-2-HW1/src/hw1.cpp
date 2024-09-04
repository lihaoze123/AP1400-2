#include "hw1.h"

Matrix algebra::zeros(size_t n, size_t m) {
    Matrix res(n, std::vector<double>(m));
    return res;
}

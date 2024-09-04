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
};

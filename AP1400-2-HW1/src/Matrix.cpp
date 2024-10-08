#include "hw1.h"

Matrix::Matrix (size_t n, size_t m, std::function<double()> f) {
    *this = Matrix(n, m);

    for (auto &x : _data) 
        for (auto &y : x) 
            y = f();
}

size_t Matrix::size() const {
    return _data.size();
}

bool Matrix::empty() const {
    return _data.empty();
}

size_t Matrix::innerSize() const {
    if (_data.empty())
        return 0;

    return _data[0].size();
}

Matrix Matrix::transpose() const {
    size_t n = this->size(), m = this->innerSize();

    Matrix res(m, n);

    for (size_t i = 0; i < m; ++ i) 
        for (size_t j = 0; j < n; ++ j)
            res[i][j] = (*this)[j][i];

    return res;
}

Matrix Matrix::minor(size_t n, size_t m) const {
    if (this->empty())
        throw std::logic_error("Empty matrix!");

    if (m >= this->innerSize())
        throw std::logic_error("Out of matrix!");

    size_t nn = this->size() - 1, 
           mm = this->innerSize() - 1;

    Matrix res(nn, mm);

    for (size_t i = 0; i < nn; ++ i) {
        for (size_t j = 0; j < mm; ++ j) {
            size_t ii = (i >= n) ? i + 1 : i,
                   jj = (j >= m) ? j + 1 : j;

            res[i][j] = (*this)[ii][jj];
        }
    }

    return res;
}

double Matrix::determinant() const {
    if (this->empty())
        return 1;

    size_t n = this->size(), m = this->innerSize();

    if (n != m)
        throw std::logic_error("Not a square matrix!");

    if (n == 1 && m == 1)
        return _data[0][0];

    double res = 0;
    
    for (size_t i = 0; i < n; ++ i) {
        auto minor = this->minor(i, 0);
        int sign = i & 1 ? -1 : 1;

        res += sign * (*this)[i][0] * minor.determinant();
    }

    return res;
}

Matrix Matrix::inv() const {
    if (this->empty())
        return Matrix();

    if (this->determinant() == 0)
        throw std::logic_error("Don't have a inv matrix!");

    size_t n = this->size(), m = this->innerSize();

    Matrix C(n, m);

    for (size_t i = 0; i < n; ++ i) {
        for (size_t j = 0; j < m; ++ j) {
            auto minor = this->minor(i, j); 
            int sign = (i + j) & 1 ? -1 : 1;

            C[i][j] = sign * minor.determinant();
        }
    }

    auto adj = C.transpose();
    auto det = this->determinant();

    auto res = algebra::multiply(adj, 1 / det);
    return res;
}

Matrix Matrix::upper_triangular() const {
    size_t n = this->size(), m = this->innerSize();

    if (n != m)
        throw std::logic_error("Not a square matrix!");

    Matrix res(*this);

    for (size_t j = 0; j < m; ++ j) {
        if (ABS(res[j][j]) <= _EPS) {
            for (size_t i = j + 1; i < n; ++ i) {
                if (ABS(res[i][j]) > _EPS) {
                    res = algebra::ero_swap(res, i, j);
                    break;
                }
            }
        }

        for (size_t i = j + 1; i < n; ++ i) {
            if (ABS(res[i][j]) > _EPS) {
                double factor = - res[i][j] / res[j][j]; 
                res = algebra::ero_sum(res, j, factor, i);
            }
        }
    }

    return res;
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
    if (index >= this->size())
        throw std::logic_error("Out of matrix!");

    return _data[index];
}

const std::vector<double>& Matrix::operator[] (size_t index) const {
    if (index >= this->size())
        throw std::logic_error("Out of matrix!");

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



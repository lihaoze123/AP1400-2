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



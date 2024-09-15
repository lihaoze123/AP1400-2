#ifndef Q1_H
#define Q1_H

#include <functional>
#include <iostream>

constexpr double EPS = 1e-8, MAX_ITER = 10000;

namespace q1 {
    inline double grad(double x, const std::function<double(double)> &f) {
        return (f(x) - f(x - EPS)) / EPS;
    }

    inline auto gradient_descent = [] (double x, double step, const std::function<double(double)>& f) {
        for (int i = 1; i <= MAX_ITER; ++ i) {
            auto now_grad = grad(x, f);

            if (std::abs(now_grad) < EPS)
                break;

            x -= step * now_grad;
        }
        return x;
    };
};

#endif //Q1_H
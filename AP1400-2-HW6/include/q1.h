#ifndef Q1_H
#define Q1_H

#include <functional>
#include <iostream>

constexpr double EPS = 1e-8;
constexpr int MAX_ITER = 2000;

namespace q1 {
    template<typename T, typename Func>
    T grad(T x, Func f) {
        return (f(x) - f(x - EPS)) / EPS;
    }

    template <typename T, typename Func>
    T gradient_descent(T x, T step, Func f = Func{}) {
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
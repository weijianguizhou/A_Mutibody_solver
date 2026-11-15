#pragma once
#include <Eigen/Dense>

namespace mbs {

template <int N, int M, class F>
Eigen::Matrix<double, M, N> jacobian(const F& c,
                                     const Eigen::Matrix<double, N, 1>& q,
                                     double h = 1e-7) {
    Eigen::Matrix<double, M, N> J;

    for (int j = 0; j < N; ++j) {
        Eigen::Matrix<double, N, 1> qp = q;
        Eigen::Matrix<double, N, 1> qm = q;
        qp(j) += h;
        qm(j) -= h;
        J.col(j) = (c(qp) - c(qm)) / (2.0 * h);
    }

    return J;
}

} // namespace mbs

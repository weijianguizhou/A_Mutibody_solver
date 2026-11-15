#pragma once

#include <Eigen/Dense>

#include <iostream>
namespace mbs {

inline Eigen::MatrixXd demo_matrix() {
    Eigen::MatrixXd a{
        {1, 2},
        {2, 3}
    };
    return a;
}
inline Eigen::VectorXd rk4_step(
    const std::function<Eigen::VectorXd(double, const Eigen::VectorXd&)>& f,
    double t, const Eigen::VectorXd& y, double h) {
    Eigen::VectorXd k1 = f(t, y);
    Eigen::VectorXd k2 = f(t + h / 2.0, y + h * k1 / 2.0);
    Eigen::VectorXd k3 = f(t + h / 2.0, y + h * k2 / 2.0);
    Eigen::VectorXd k4 = f(t + h, y + h * k3);

    return y + (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}


inline void print_matrix(const Eigen::MatrixXd& mat) {
    std::cout << mat << std::endl;
}

}

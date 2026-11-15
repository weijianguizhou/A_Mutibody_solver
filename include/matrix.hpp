#pragma once

#include <Eigen/Dense>

#include <iostream>

namespace mbs {

inline Eigen::MatrixXf demo_matrix() {
    Eigen::MatrixXf a{
        {1, 2},
        {2, 3}
    };
    return a;
}

inline void print_matrix(const Eigen::MatrixXf &mat) {
    std::cout << mat << std::endl;
}

}

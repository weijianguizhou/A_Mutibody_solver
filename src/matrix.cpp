#include "matrix.hpp"

#include <iostream>

namespace mbs {

Eigen::MatrixXf demo_matrix() {
    Eigen::MatrixXf a{
        {1, 2},
        {2, 3}
    };
    return a;
}

void print_matrix(const Eigen::MatrixXf &mat) {
    std::cout << mat << std::endl;
}

}

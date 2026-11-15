#include <iomanip>
#include <iostream>

#include "demo1.h"
#include "jacobian.h"

#include <windows.h>


namespace {
void show_demo1() {
    mbs::Demo1Model model;

    const Eigen::Vector4d q(1.0, 0.0, 1.28, 0.96);
    const Eigen::Vector4d qdot(0.0, 1.0, 0.96, 0.72);

    const Eigen::Matrix4d M = model.mass_matrix();
    const Eigen::Matrix<double, 3, 4> cq =mbs::jacobian<4, 3>([&](const Eigen::Vector4d& x) { return model.constraints(x); }, q);
    const Eigen::Vector3d c = model.constraints(q);
    const Eigen::Vector4d Q = model.generalized_force();
    const Eigen::Vector3d eps = model.velocity_rhs(q, qdot);

    std::cout << "\n--- demo1: 两质点四连杆机构 (习题三 问题一) ---\n";
    std::cout << "参数: l1=" << model.l1 << "  l2=" << model.l2 << "  l3=" << model.l3
              << "  l4=" << model.l4 << "\n";
    std::cout << "      m1=" << model.m1 << "  m2=" << model.m2 << "  g=" << model.g << "\n\n";

    std::cout << "q0    = " << q.transpose() << "\n";
    std::cout << "qdot0 = " << qdot.transpose() << "\n\n";

    std::cout << "M = m1 r1q^T r1q + m2 r2q^T r2q =\n" << M << "\n\n";
    std::cout << "c(q0) =\n" << c.transpose() << "\n\n";
    std::cout << "c_q = dc/dq =\n" << cq << "\n\n";
    std::cout << "Q =\n" << Q.transpose() << "\n\n";
    std::cout << "eps =\n" << eps.transpose() << "\n\n";

    Eigen::Matrix<double, 7, 7> A = Eigen::Matrix<double, 7, 7>::Zero();
    A.topLeftCorner<4, 4>() = M;
    A.topRightCorner<4, 3>() = cq.transpose();
    A.bottomLeftCorner<3, 4>() = cq;

    Eigen::Matrix<double, 7, 1> b;
    b.head<4>() = Q;
    b.tail<3>() = eps;

    std::cout << "[M c_q^T; c_q 0] =\n" << A << "\n\n";

    const Eigen::Matrix<double, 7, 1> sol = A.partialPivLu().solve(b);

    std::cout << "qddot  = " << sol.head<4>().transpose() << "\n";
    std::cout << "lambda = " << sol.tail<3>().transpose() << "\n";
    std::cout << "残差   = " << (A * sol - b).norm() << "\n";
    std::cout << "c_q*qddot - eps 残差 = " << (cq * sol.head<4>() - eps).norm() << "\n";
}

}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << std::setprecision(6);

    for (;;) {
        std::cout << "\n==== my_solver ====\n"
                  << "  1. demo1  两质点四连杆机构\n"
                  << "  0. 退出\n"
                  << "请选择: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            break; // EOF 或不是数字, 直接退出
        }

        if (choice == 0) {
            break;
        }
        if (choice == 1) {
            show_demo1();
        }
    }

    std::cout << "已退出。\n";
    return 0;
}

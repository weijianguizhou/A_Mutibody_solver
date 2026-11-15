#pragma once
#include <Eigen/Dense>

namespace mbs {

struct Demo1Model {
	// 几何与惯性参数，单位用SI制
    double l1 = 1.000; 
    double l2 = 1.000; 
    double l3 = 1.200; 
    double l4 = 2.000; 
    double m1 = 1.000;
    double m2 = 1.000;
    double g = 9.800;

    // 广义质量阵
    Eigen::Matrix4d mass_matrix() const {
        Eigen::Matrix4d M = Eigen::Matrix4d::Zero();
        M(0, 0) = m1;
        M(1, 1) = m1;
        M(2, 2) = m2;
        M(3, 3) = m2;
        return M;
    }

    // 约束方程 
    Eigen::Vector3d constraints(const Eigen::Vector4d& q) const {
        const double x1 = q(0);
        const double y1 = q(1);
        const double x2 = q(2);
        const double y2 = q(3);

        return Eigen::Vector3d{
            x1 * x1 + y1 * y1 - l1 * l1,
            (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) - l2 * l2,
            (x2 - l4) * (x2 - l4) + y2 * y2 - l3 * l3};
    }

    // 广义力列阵
    Eigen::Vector4d generalized_force() const {
        return Eigen::Vector4d{0.0, -m1 * g, 0.0, -m2 * g};
    }

    // 加速度约束右端项
    Eigen::Vector3d velocity_rhs(const Eigen::Vector4d& q,
                                 const Eigen::Vector4d& qdot) const {
        const double dx1 = qdot(0);
        const double dy1 = qdot(1);
        const double dx2 = qdot(2);
        const double dy2 = qdot(3);

        return Eigen::Vector3d{
            -2.0 * (dx1 * dx1 + dy1 * dy1),
            -2.0 * ((dx1 - dx2) * (dx1 - dx2) + (dy1 - dy2) * (dy1 - dy2)),
            -2.0 * (dx2 * dx2 + dy2 * dy2)};
    }
};

} // namespace mbs

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense> 

class Transform {
public:
    Eigen::Matrix4d matrix;      // Transformation matrix
    Eigen::Matrix4d invMatrix;   // Inverse of the transformation matrix

    // Constructor to initialize the transform with an identity matrix
    Transform() : matrix(Eigen::Matrix4d::Identity()), invMatrix(Eigen::Matrix4d::Identity()) {}

    // Constructor for custom matrix
    Transform(const Eigen::Matrix4d& m) : matrix(m), invMatrix(m.inverse()) {}

    // Apply transformation to a point
    Eigen::Vector4d apply(const Eigen::Vector4d& point) const {
        return matrix * point;
    }

    // Apply inverse transformation (useful for rays)
    Eigen::Vector4d applyInverse(const Eigen::Vector4d& point) const {
        return invMatrix * point;
    }

    // Factory methods for common transformations
    static Transform translate(const Eigen::Vector3d& offset) {
        Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
        m(0, 3) = offset.x();
        m(1, 3) = offset.y();
        m(2, 3) = offset.z();
        return Transform(m);
    }

    static Transform scale(double sx, double sy, double sz) {
        Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
        m(0, 0) = sx;
        m(1, 1) = sy;
        m(2, 2) = sz;
        return Transform(m);
    }

    static Transform rotateX(double angle) {
        Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
        double c = cos(angle), s = sin(angle);
        m(1, 1) = c; m(1, 2) = -s;
        m(2, 1) = s; m(2, 2) = c;
        return Transform(m);
    }

    static Transform rotateY(double angle) {
        Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
        double c = cos(angle), s = sin(angle);
        m(0, 0) = c; m(0, 2) = s;
        m(2, 0) = -s; m(2, 2) = c;
        return Transform(m);
    }

    static Transform rotateZ(double angle) {
        Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
        double c = cos(angle), s = sin(angle);
        m(0, 0) = c; m(0, 1) = -s;
        m(1, 0) = s; m(1, 1) = c;
        return Transform(m);
    }
};

#endif
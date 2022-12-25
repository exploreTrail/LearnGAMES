#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Geometry>
#include <iostream>

using namespace std;

#define pi 3.14159265359

int main()
{
    Eigen::Vector3d p(2, 1, 0);
    cout << p << endl;
    Eigen::AngleAxisd angle_axis(pi / 4, Eigen::Vector3d(0, 0, 0));
    Eigen::Vector3d rotated_v1 = angle_axis.matrix().inverse() * p;
    cout << angle_axis.matrix() << endl;
    cout << rotated_v1 << endl;
    Eigen::Vector3d t(1, 2, 0);
    rotated_v1 = rotated_v1 + t;
    cout << rotated_v1.transpose() << endl;
    // // Basic Example of cpp
    // cout << "Example of cpp \n";
    // float a = 1.0, b = 2.0;
    // cout << a << endl;
    // cout << a / b << endl;
    // cout << sqrt(b) << endl;
    // cout << acos(-1) << endl;
    // cout << sin(30.0 / 180.0 * acos(-1)) << endl;

    // // Example of vector
    // cout << "Example of vector \n";
    // // vector definition
    // Eigen::Vector3f v(1.0f, 2.0f, 3.0f);
    // Eigen::Vector3f w(1.0f, 0.0f, 0.0f);
    // // vector output
    // cout << "Example of output \n";
    // cout << v << endl;
    // // vector add
    // cout << "Example of add \n";
    // cout << v + w << endl;
    // // vector scalar multiply
    // cout << "Example of scalar multiply \n";
    // cout << v * 3.0f << endl;
    // cout << 2.0f * v << endl;

    // // Example of matrix
    // cout << "Example of matrix \n";
    // // matrix definition
    // Eigen::Matrix3f i, j;
    // i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    // j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // // matrix output
    // cout << "Example of output \n";
    // cout << i << endl;
    // // matrix add i + j
    // // matrix scalar multiply i * 2.0
    // // matrix multiply i * j
    // // matrix multiply vector i * v

    return 0;
}
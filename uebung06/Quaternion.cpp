/**
 *  @file Quaternion.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Quaternion.hpp"
#include "Matrix.hpp"

namespace asteroids
{

Quaternion::Quaternion()
{
    // Default Quaternion
    x = 1.0;
    y = 0.0;
    z = 0.0;
    w = 0.0;
}

Quaternion::~Quaternion()
{
    // Do nothing
}

Quaternion::Quaternion(const Vector& vec, float angle)
{
    // Calculate the quaternion
    fromAxis(vec, angle);
}

Quaternion::Quaternion(float _x, float _y, float _z, float _angle)
{
    // Set the values
    x = _x;
    y = _y;
    z = _z;
    w = _angle;
}

Quaternion::Quaternion(float* vec, float _w)
{
    // Set the values
    x = vec[0];
    y = vec[1];
    z = vec[2];
    w = _w;
}

void Quaternion::fromAxis(const Vector& axis, float angle)
{
    float sinAngle;
    angle *= 0.5f;

    // Create a copy of the given vector and normalize the new vector
    Vector vn(axis.x, axis.y, axis.z);
    vn.normalize();

    // Calculate the sinus of the given angle
    sinAngle = sin(angle);

    // Get the quaternion
    x = (vn.x * sinAngle);
    y = (vn.y * sinAngle);
    z = (vn.z * sinAngle);
    w = cos(angle);
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
    return Quaternion(w * other.x + x * other.w + y * other.z - z * other.y,
                      w * other.y + y * other.w + z * other.x - x * other.z,
                      w * other.z + z * other.w + x * other.y - y * other.x,
                      w * other.w - x * other.x - y * other.y - z * other.z);
}

Quaternion Quaternion::getConjugate() const
{
    return Quaternion(-x, -y, -z, w);
}

Vector Quaternion::operator*(const Vector& other) const
{
    Vector vn(other);
    vn.normalize();

    Quaternion vecQuat, resQuat;
    vecQuat.x = vn.x;
    vecQuat.y = vn.y;
    vecQuat.z = vn.z;
    vecQuat.w = 0.0f;

    resQuat = vecQuat * getConjugate();
    resQuat = *this * resQuat;

    return (Vector(resQuat.x, resQuat.y, resQuat.z));
}

void Quaternion::print()
{
    std::cout << "Quaternion: " << x << ", " << y << ", " << z << ", " << w << std::endl;
}

Matrix Quaternion::toMatrix() const
{
    Matrix m;
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;

    float yy = y * y;
    float yz = y * z;
    float yw = y * w;

    float zz = z * z;
    float zw = z * w;

    m[0][0] = 1 - 2 * (yy + zz);
    m[0][1] = 2 * (xy - zw);
    m[0][2] = 2 * (xz + yw);

    m[1][0] = 2 * (xy + zw);
    m[1][1] = 1 - 2 * (xx + zz);
    m[1][2] = 2 * (yz - xw);

    m[2][0] = 2 * (xz - yw);
    m[2][1] = 2 * (yz + xw);
    m[2][2] = 1 - 2 * (xx + yy);


    return m;

}

/* Matrix Quaternion::toMatrix() const
{
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    Matrix mat;
    float* m = mat.getData();

    m[0]  = 1.0f - 2.0f * (y2 + z2);
    m[1]  = 2.0f * (xy - wz);
    m[2]  = 2.0f * (xz + wy);
    m[3]  = 0.0f;
    m[4]  = 2.0f * (xy + wz);
    m[5]  = 1.0f - 2.0f * (x2 + z2);
    m[6]  = 2.0f * (yz - wx);
    m[7]  = 0.0f;
    m[8]  = 2.0f * (xz - wy);
    m[9]  = 2.0f * (yz + wx);
    m[10] = 1.0f - 2.0f * (x2 + y2);
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;

    return mat;
} */
}

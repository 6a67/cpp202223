//
// Created by sascha on 11.12.22.
//

#ifndef MATRIXPROXY_HPP
#define MATRIXPROXY_HPP

namespace asteroids
{

class MatrixProxy
{
public:
    MatrixProxy(float* data, int size);

    float& operator[](int index);

private:
    // pointer to the first element of the row
    // points to the array inside the matrix
    float* m_row;

    int m_size;
};

}  // namespace asteroids
#endif
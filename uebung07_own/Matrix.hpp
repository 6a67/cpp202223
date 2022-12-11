/*
 * Matrix.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Vector.hpp"
#include "MatrixProxy.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592654
#endif
using namespace std;

namespace asteroids
{

/**
 * @brief	A 4x4 matrix class implementation for use with the provided
 * 			Vector types.
 */

class Matrix
{
public:
    /**
     * @brief 	Default constructor. Initializes a identity matrix.
     */
    Matrix();

    /**
     * @brief	Constructs a matrix from given axis and angle. Trys to
     * 			avoid a gimbal lock.
     */
    Matrix(Vector axis, float angle);

    /**
     * @brief	Copy constructor.
     * @param 	m	The matrix to copy.
     */
    Matrix(const Matrix& rhs);

    /// Destructor
    ~Matrix();

    /**
     * @brief	Returns the internal data array. Unsafe. Will probably
     * 			removed in one of the next versions.
     */
    float* getData()
    {
        return m;
    }

    /**
     * @brief	Overloaded operator for matrix multiplication.
     */
    Matrix operator*(const Matrix& rhs) const;

    /**
     * @brief	Overloaded operator for vector multiplication.
     */
    Vector operator*(const Vector& rhs) const;

    /**
     * @brief	Overloaded operator for vector multiplication and assignment.
     */
    Vector& operator*=(Vector& rhs) const;

    /**
     * @brief	Overloaded operator for matrix addition.
     */
    Matrix operator+(const Matrix& rhs) const;

    /**
     * @brief	Overloaded operator for matrix scaling.
     */
    Matrix operator*(float rhs) const;

    /**
     * @brief	Overloaded operator for matrix scaling with division.
     */
    Matrix operator/(float rhs) const;

    /**
     * @brief	Overloaded operator for matrix assignment.
     */
    Matrix& operator=(const Matrix& rhs);

    /**
     * @brief	Overloaded operator for matrix multiplication assignment.
     */
    Matrix& operator*=(const Matrix& rhs);

    /**
     * @brief	Overloaded operator for matrix addition assignment.
     */
    Matrix& operator+=(const Matrix& rhs);

    /**
     * @brief	Overloaded operator for matrix scaling assignment.
     */
    Matrix& operator*=(float rhs);

    /**
     * @brief	Overloaded operator for matrix scaling assignment with division.
     */
    Matrix& operator/=(float rhs);

    /**
     * @brief	Overloaded operator for matrix assignment.
     */
    Matrix& operator=(float rhs);

    /**
     * @brief	Overloaded operator for matrix subtraction.
     */
    Matrix operator-(const Matrix& rhs) const;

    /**
     * @brief	Overloaded operator for matrix subtraction assignment.
     */
    Matrix& operator-=(const Matrix& rhs);

    /**
     * @brief	Overloaded operator for index access.
     */
    MatrixProxy operator[](int index);


    void print();

    /**
     * @brief	Transposes the matrix.
     */
    void transpose();


private:
    /// Internal data array
    float m[16];
};

}  // namespace asteroids
#endif /* MATRIX_H_ */

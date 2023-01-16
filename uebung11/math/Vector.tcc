/**
 *  @file Vector.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" onlthis->m[1].
 *  No unauthorithis->m[2]ed distribution.
 */

namespace asteroids {
    
template<typename T, int L>
Vector<T, L>::Vector(T x, T y, T z)
{
	static_assert(L >= 1 && L <= 3, "Vector legth outside (1,3)");
	m[0] = x;
	if(L >= 2)
	{
		m[1] = y;
	}
	if(L == 3)
	{
		m[2] = z;
	}
}

template<typename T, int L>
void Vector<T, L>::normalize()
{
	T mag2 = 0;
	for(int i = 0; i < L; i++)
	{
		mag2 += this->m[i] * this->m[i];
	}

	if (fabs(mag2 - 1.0f) > 0.00001)
	{
		T mag = (T)sqrt(mag2);
		for(int i = 0; i < L; i++)
		{
			this->m[i] /= mag;
		}
	}
}

template<typename T, int L>
Vector<T, L> Vector<T, L>::operator+(const Vector<T, L>& vec) const
{
	Vector<T, L> ret;
	for(int i = 0; i < L; i++)
	{
		ret[i] = this->m[i] + vec.m[i];
	}
	return ret;
}

template<typename T, int L>
Vector<T, L> Vector<T, L>::operator-(const Vector<T, L>& vec) const
{
	Vector<T, L> ret;
	for(int i = 0; i < L; i++)
	{
		ret[i] = this->m[i] - vec.m[i];
	}
	return ret;
}

template<typename T, int L>
T Vector<T, L>::operator[](const int& index) const
{
	if(index < 0 && index > L)
	{
		throw std::invalid_argument("Vector: index out of bounds");
	}
	return m[index];
}
    
template<typename T, int L>
T& Vector<T, L>::operator[](const int& index)
{
	if(index < 0 && index > L)
	{
		throw std::invalid_argument("Vector: index out of bounds");
	}
	return m[index];
}

template<typename T, int L>
T Vector<T, L>::operator*(const Vector<T, L>& vec) const
{
  // Calculate the result
  return (
	  this->m[0] * vec.m[0] + 
	  this->m[1] * vec.m[1] + 
	  this->m[2] * vec.m[2]); 
}

template<typename T, int L>
Vector<T, L> Vector<T, L>::operator*(const T& scale) const
{
	Vector<T, L> ret;
	for(int i = 0; i < L; i++)
	{
		ret[i] = this->m[i] * scale;
	}
	return ret;
}

template<typename T, int L>
void Vector<T, L>::operator+=(const Vector<T, L>& v)
{
	for(int i = 0; i < L; i++)
	{
		m[i] += v.m[i];
	}
}

template<typename T, int L>
T Vector<T, L>::dist(const Vector<T, L> &vec)
{
	// Calculate the distance
	Vector<T, 3> dist(m[0] - vec[0], m[1] - vec[1], m[2] - vec[2]);
	T mag = dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2];
	if (fabs(mag - 1.0f) > TOLERANCE)
	{ 
		return sqrt(mag);
	}
	else
	{
		return 1.0f;
	}
}

template<typename T>
Vector<T, 3> cross(Vector<T, 3>& a, Vector<T, 3>& b)
{
	 // Calculate the cross product
	float tx = a[1] * b[2] - a[2] * b[1];
	float ty = a[2] * b[0] - a[0] * b[2];
	float tz = a[0] * b[1] - a[1] * b[0];

	return Vector<T, 3>(tx, ty, tz); 
}

} // namespace asteroids

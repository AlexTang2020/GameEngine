#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D(): x(0), y(0), z(0)
{
}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{
}


float Vector3D::Magnitude() const
{
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

void Vector3D::Normalize()
{
	float mag = Magnitude();
	x = x / mag;
	y = y / mag;
	z = z / mag;
}

Vector3D Vector3D::Normal() const
{
	float mag = Magnitude();
	return Vector3D(x/mag, y/mag, z/mag);
}

Vector3D Vector3D::operator+(Vector3D const &right) 
{ 
	return Vector3D(right.x + x, right.y + y, right.z + z); 
}

Vector3D Vector3D::operator*(float val)
{
	return Vector3D(val * x, val * y, val * z);
}

void Vector3D::add(Vector3D const & right)
{
	x += right.x;
	y += right.y;
	z += right.z;
}

void Vector3D::scale(float val)
{
	x *= val;
	y *= val;
	z *= val;
}

float Vector3D::Dot(Vector3D const & right)
{
	return x * right.x + y * right.y + z * right.z;
}

Vector3D Vector3D::Cross(Vector3D const & right)
{
	return Vector3D(y * right.z - z * right.y, z * right.x - x * right.z, x * right.y - y * right.x);
}

Vector3D Vector3D::Lerp(Vector3D & right, float val)
{
	return Vector3D((1-val)*x + val * right.x, (1-val)*y + right.y, (1-val)*z + val * right.z);
}

//Change for general use, need 2 Vectors
float Dot(Vector3D const & right, Vector3D const & left)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3D Cross(Vector3D const & left, Vector3D const & right)
{
	return Vector3D(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
}

Vector3D Lerp(Vector3D & left, Vector3D & right, float val)
{
	return right*(val) + left*(1.0f - val);
}

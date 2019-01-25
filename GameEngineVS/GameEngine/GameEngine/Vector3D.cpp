#include "Vector3D.h"

Vector3D::Vector3D(): x(0), y(0), z(0)
{
}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{
}

//Will need to create
float Vector3D::Magnitude() const
{
	return 0.0f;
}

void Vector3D::Normalize()
{
}

Vector3D Vector3D::Normal() const
{
	return Vector3D();
}


void Vector3D::add(Vector3D const & right)
{
	x += right.x;
	y += right.y;
	z += right.z;
}

void Vector3D::scale(Vector3D const & right)
{
	x *= right.x;
	y *= right.y;
	z *= right.z;
}

float Vector3D::Dot(Vector3D const & right)
{
	return 0.0f;
}

Vector3D Vector3D::Cross(Vector3D const & right)
{
	return Vector3D();
}

Vector3D Vector3D::Lerp(Vector3D & left, float val)
{
	return Vector3D();
}

Vector3D Vector3D::Perpendicular(Vector3D & left, Vector3D & right)
{
	return Vector3D();
}

//Change for general use, need 2 Vectors
float Dot(Vector3D const & right)
{
	return 0.0f;
}

Vector3D Cross(Vector3D const & right)
{
	return Vector3D();
}

Vector3D Lerp(Vector3D & left, float val)
{
	return Vector3D();
}

Vector3D Perpendicular(Vector3D & left, Vector3D & right)
{
	return Vector3D();
}

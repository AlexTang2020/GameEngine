#include "Point3D.h"

Point3D::Point3D(): x(0), y(0), z(0)
{
}

Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3D Point3D::operator-(Point3D const & right)
{
	return Vector3D(x-right.x, y-right.y, z-right.z);
}

Point3D Point3D::operator+(Vector3D const & right)
{
	return Point3D(x+right.z, y+right.y, z+right.z);
}

void Point3D::add(Vector3D const & right)
{
	x += right.x;
	y += right.y;
	z += right.z;
}

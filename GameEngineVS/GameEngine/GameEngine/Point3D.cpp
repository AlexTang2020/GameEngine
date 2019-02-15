#include "Point3D.h"

Point3D::Point3D(): x(0), y(0), z(0), w(1)
{
}

Point3D::Point3D(float x, float y, float z, int w) : x(x), y(y), z(z)
{
}

Vector3D Point3D::operator-(Point3D const & right)
{
	return Vector3D(x-right.x, y-right.y, z-right.z);
}

Point3D Point3D::operator+(Vector3D const & right)
{
	return Point3D(x+right.x, y+right.y, z+right.z);
}

void Point3D::add(Vector3D const & right)
{
	x += right.x;
	y += right.y;
	z += right.z;
}

void Point3D::concatenate(Matrix4 & right)
{
	float vx = x;
	float vy = y;
	float vz = z;
	float vw = w;

	x = vx * right.mat4[0][0] + vy * right.mat4[1][0] + vz * right.mat4[2][0] + vw * right.mat4[3][0];
	y = vx * right.mat4[0][1] + vy * right.mat4[1][1] + vz * right.mat4[2][1] + vw * right.mat4[3][1];
	z = vx * right.mat4[0][2] + vy * right.mat4[1][2] + vz * right.mat4[2][2] + vw * right.mat4[3][2];
	w = vx * right.mat4[0][3] + vy * right.mat4[1][3] + vz * right.mat4[2][3] + vw * right.mat4[3][3];
}

#include "Quaternion.h"

Quaternion::Quaternion() : qx(0), qy(0), qz(0), qw(0)
{
}

Quaternion::Quaternion(float qx, float qy, float qz, float qw) : qx(qx), qy(qy), qz(qz), qw(qw)
{
}

Quaternion Quaternion::operator+(Quaternion const & right)
{
	return Quaternion(qx + right.qx, qy + right.qy, qz + right.qz, qw + right.qw);
}

Quaternion Quaternion::operator-(Quaternion const & right)
{
	return Quaternion(qx - right.qx, qy - right.qy, qz - right.qz, qw - right.qw);
}

Quaternion Quaternion::operator*(Quaternion const & right)
{
	return Quaternion(qw*right.qw - qx * right.qx - qy * right.qy - qz * right.qz,
		qw*right.qx + qx * right.qw + qy * right.qz - qz * right.qy,
		qw*right.qy + qy * right.qw + qz * right.qx - qx * right.qz,
		qw*right.qz + qz * right.qw + qx * right.qy - qy * right.qx);
}


Quaternion Quaternion::operator+=(Quaternion const & right)
{
	qx += right.qx;
	qy += right.qy;
	qz += right.qz;
	qw += right.qw;
	return (*this);
}

Quaternion Quaternion::operator-=(Quaternion const & right)
{
	qx -= right.qx;
	qy -= right.qy;
	qz -= right.qz;
	qw -= right.qw;
	return (*this);
}

Quaternion Quaternion::operator*=(Quaternion const & right)
{
	qx = qw * right.qw - qx * right.qx - qy * right.qy - qz * right.qz;
	qy = qw * right.qx + qx * right.qw + qy * right.qz - qz * right.qy;
	qz = qw * right.qy + qy * right.qw + qz * right.qx - qx * right.qz;
	qw = qw * right.qz + qz * right.qw + qx * right.qy - qy * right.qx;
	return (*this);
}



Quaternion Quaternion::scale(float val)
{
	return Quaternion(qx*val, qy*val, qz*val, qw*val);
}



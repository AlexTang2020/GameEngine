#define _USE_MATH_DEFINES

#include "Quaternion.h"
#include <cmath>

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
	return Quaternion(qw*right.qx + qx * right.qw + qy * right.qz - qz * right.qy,
		qw*right.qy + qy * right.qw + qz * right.qx - qx * right.qz,
		qw*right.qz + qz * right.qw + qx * right.qy - qy * right.qx,
		qw*right.qw - qx * right.qx - qy * right.qy - qz * right.qz);
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
	qx = qw * right.qx + qx * right.qw + qy * right.qz - qz * right.qy;
	qy = qw * right.qy + qy * right.qw + qz * right.qx - qx * right.qz;
	qz = qw * right.qz + qz * right.qw + qx * right.qy - qy * right.qx;
	qw = qw * right.qw - qx * right.qx - qy * right.qy - qz * right.qz;
		
	return (*this);
}



Quaternion Quaternion::scale(float val)
{
	return Quaternion(qx*val, qy*val, qz*val, qw*val);
}

float Quaternion::norm()
{
	return sqrt(qw*qw + qx*qx + qy*qy + qz*qz);
}

void Quaternion::normalize()
{
	if (norm() != 0) {
		float normVal = 1 / norm();
		qw *= normVal;
		qx *= normVal;
		qy *= normVal;
		qz *= normVal;
	}
}

void Quaternion::convertToUnitFormQuaternion()
{
	double angle = qw * M_PI / 180.f;
	Vector3D v = Vector3D(qx,qy,qz);
	v.Normalize();
	qw *= (float) cosf(angle * 0.5f);
	v.scale((float) sinf(angle * 0.5f), (float) sinf(angle * 0.5f), sinf(angle * 0.5f));
	qx = v.x;
	qy = v.y; 
	qz = v.z;
}

Quaternion Quaternion::inverse()
{
	float absVal = norm();
	absVal *= absVal;
	absVal = 1 / absVal;

	Quaternion conjVal = conjugate();

	float scalar = conjVal.qw * absVal;
	float x = conjVal.qx * absVal;
	float y = conjVal.qy * absVal;
	float z = conjVal.qz * absVal;

	return Quaternion(x,y,z,scalar);
}

Quaternion Quaternion::conjugate()
{
	return Quaternion(qx * -1, qy * -1, qz * -1, qw);
}

Vector3D Quaternion::quaternionToVector(float angle) {	
	//Only function not tested, may not be used or will be remade to another function
	//Maybe Quaternion to Euler Angle in vector form
	return Vector3D((float) qx*sin((M_PI*angle/180.f)/2.f), (float) qy*sin((M_PI*angle / 180.f) / 2.f), (float) qz*sin((M_PI*angle/180.f)/2.f), (int) cos((M_PI*angle/180.f)/2.f));
}

Matrix4 Quaternion::quaternionToMatrix4()
{
	Matrix4 qToM = Matrix4();
	qToM.mat4[0][0] = 1 - 2 * qy*qy - 2 * qz*qz;
	qToM.mat4[0][1] = 2 * qx*qy - 2 * qz*qw;
	qToM.mat4[0][2] = 2 * qx*qz + 2 * qy*qw;
	
	qToM.mat4[1][0] = 2 * qx*qy + 2 * qz*qw;
	qToM.mat4[1][1] = 1 - 2 * qx*qx - 2 * qz*qz;
	qToM.mat4[1][2] = 2 * qy*qz - 2 * qx*qw;
	
	qToM.mat4[2][0] = 2 * qx*qz - 2 * qy*qw;
	qToM.mat4[2][1] = 2 * qy*qz + 2 * qx*qw;
	qToM.mat4[2][2] = 1 - 2 * qx*qx - 2 * qy*qy;

	return qToM;
}

#pragma once
#include "Vector3D.h"
#include <math.h>

class Quaternion
{
public:
	float qx = 0;
	float qy = 0;
	float qz = 0;
	float qw = 0;

	Quaternion();

	explicit Quaternion(float qx, float qy, float qz, float qw);

	// member functions
	Quaternion operator+(Quaternion const& right);
	Quaternion operator-(Quaternion const& right);
	Quaternion operator*(Quaternion const& right);

	Quaternion operator+=(Quaternion const& right);
	Quaternion operator-=(Quaternion const& right);
	Quaternion operator*=(Quaternion const& right);

	Quaternion scale(float val);
	float norm();
	void normalize();
	void convertToUnitFormQuaternion();
	Quaternion inverse();
	Quaternion conjugate();
	Matrix4 quaternionToMatrix4();
};
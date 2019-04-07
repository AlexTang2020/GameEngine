#pragma once
#include "Vector3D.h"
#include "Matrix4.h"
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
	Quaternion operator+(Quaternion const& right);	//Return sum of two quaternions
	Quaternion operator-(Quaternion const& right);	//Return difference of two quaternions
	Quaternion operator*(Quaternion const& right);	//Return product of two quaterions

	Quaternion operator+=(Quaternion const& right);	//Return sum of two quaternions, overwrites current quaternion
	Quaternion operator-=(Quaternion const& right); //Return difference of two quaternions, overwrites current quaternion
	Quaternion operator*=(Quaternion const& right); //Return product of two quaterions, overwrites current quaternion

	Quaternion scale(float val);	//Scales each value in quaternion by val 
	float norm();					//Returns normal of quaternion
	void normalize();				//Normalizes quaternion
	void convertToUnitFormQuaternion();	//Convert to normalized vector
	Quaternion inverse();				//Returns inverse of quaternion
	Quaternion conjugate();				//Returns conjugate of quaternion
	Vector3D quaternionToVector(float angle);	//Return Vector3D of quaternion rotated by an angle
	Matrix4 quaternionToMatrix4();				//Return Matrix4 of quaternion
};
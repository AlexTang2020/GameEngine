#pragma once
#include <math.h>
#include "Vector3D.h"

class Point3D
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Point3D();

	explicit Point3D(float x, float y, float z);

	// member functions
	Vector3D operator-(Point3D const& right);
	Point3D operator+(Vector3D const& right);

	void add(Vector3D const& right);


private:

};
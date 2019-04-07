#pragma once
#include <math.h>
#include "Vector3D.h"
#include "Matrix4.h"

class Point3D
{
public:
	float x = 0;	// x position
	float y = 0;	// y position
	float z = 0;	// z position
	int w = 1;		

	Point3D();

	explicit Point3D(float x, float y, float z, int w = 1);

	// member functions
	Vector3D operator-(Point3D const& right);	//Return vector that is the difference between 2 points
	Point3D operator+(Vector3D const& right);	//Return point location after moved by a vector

	void add(Vector3D const& right);	//Change position of point by a vector
	void concatenate(Matrix4& right);	//Multiply vector with Matrix4

private:

};
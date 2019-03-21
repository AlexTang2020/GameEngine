#pragma once
#include "Point3D.h"
#include "Vector3D.h"

class Vertex3D
{
public:
	Point3D location;
	float s = 0.0f;
	float t = 0.0f;
	Vector3D normal;

	Vertex3D();
	Vertex3D(float x, float y, float z);
	Vertex3D(float x, float y, float z, float sVal, float tVal);
	~Vertex3D();

	void setLocation(float x, float y, float z);
	void setS(float sVal);
	void setT(float tVal);
	void setNormal(Vector3D norm);

private:

};

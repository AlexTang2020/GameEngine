#pragma once
#include "Point3D.h"

class Vertex3D
{
public:
	Point3D location;
	float s;
	float t;
	float normal;

	Vertex3D();
	~Vertex3D();

private:

};

Vertex3D::Vertex3D()
{
}

Vertex3D::~Vertex3D()
{
}

#include "Vertex3D.h"

Vertex3D::Vertex3D() {
	location = Point3D(0, 0, 0);
}

Vertex3D::Vertex3D(float x, float y, float z)
{
	location = Point3D(x, y, z);
}

Vertex3D::Vertex3D(float x, float y, float z, float sVal, float tVal)
{
	location = Point3D(x, y, z);
	setS(sVal);
	setT(tVal);
}

Vertex3D::~Vertex3D()
{
}


void Vertex3D::setLocation(float x, float y, float z) {
	location = Point3D(x, y, z);
}

void Vertex3D::setS(float sVal) {
	s = sVal;
}

void Vertex3D::setT(float tVal) {
	t = tVal;
}

void Vertex3D::setNormal(Vector3D norm){
	normal = norm;
}
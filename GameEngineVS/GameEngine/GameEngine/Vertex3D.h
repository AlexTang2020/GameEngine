#pragma once
#include "Point3D.h"
#include "Vector3D.h"

class Vertex3D
{
public:
	Point3D location;			//Position of vertex
	float s = 0.0f;				//S value for textures
	float t = 0.0f;				//T value for textures
	Vector3D normal;			//Normal Vector for lighting

	Vertex3D();
	Vertex3D(float x, float y, float z);
	Vertex3D(float x, float y, float z, float sVal, float tVal);
	~Vertex3D();

	void setLocation(float x, float y, float z);		//Set vertex position
	void setS(float sVal);								//Set S value
	void setT(float tVal);								//Set T value
	void setNormal(Vector3D norm);						//Set Normal Vector

private:

};

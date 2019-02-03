#pragma once
#include <math.h>


class Matrix4
{
public:
	
	float mat4[4][4];
	Matrix4();

	void setIdentity();
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);

	void inverse();
	void transpose();

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);


private:

};
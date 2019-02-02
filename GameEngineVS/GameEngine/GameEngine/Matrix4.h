#pragma once

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

	void rotateX();
	void rotateY();
	void rotateZ();


private:

};
#pragma once
#include <math.h>


class Matrix4
{
public:
	
	float mat4[4][4];	// 2D Array[row][column]
	Matrix4();
	~Matrix4();

	void setIdentity();								//Set diagonals equal to 1
	void translate(float x, float y, float z);		//Translate/Move matrix 
	void scale(float x, float y, float z);			//Multiply matrix to scale 

	void inverse();					//Inverse the matrix
	void transpose();				//Transpose the matrix

	void rotateX(float angle);		//Rotate about the x axix
	void rotateY(float angle);		//Rotate about the y axis
	void rotateZ(float angle);		//Rotate about the z axis

	void concatenate(Matrix4& right);	//Multiply matrix with another matrix on the RHS

private:

};

float* value_ptr(Matrix4 mat);		//Returns address of an array that holds all mat4 values
void printMatrix4(Matrix4 mat4);	//Prints out values stored in mat4
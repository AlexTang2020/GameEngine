#pragma once
#include <math.h>
#include "Vector3D.h"

class Matrix4
{
public:
	
	float mat4[4][4];	// 2D Array[row][column]
	Matrix4();
	~Matrix4();

	void setIdentity();				//Set diagonals equal to 1

	void inverse();					//Inverse the matrix
	void transpose();				//Transpose the matrix

	void concatenate(Matrix4& right);	//Multiply matrix with another matrix on the RHS

private:

};

Matrix4 translate(float x, float y, float z);		//Translate/Move matrix via floats
Matrix4 translate(Vector3D vec);					//Translate/Move matrix via vector
Matrix4 scale(float x, float y, float z);			//Multiply matrix to scale non-uniformly
Matrix4 scale(float val);			//Multiply matrix to scale uniformly

Matrix4 rotate(float angle, float x, float y, float z); //Rotate about specified axis
Matrix4 rotateX(float angle);		//Rotate about the x axix
Matrix4 rotateY(float angle);		//Rotate about the y axis
Matrix4 rotateZ(float angle);		//Rotate about the z axis
Matrix4 rotateAtCenter(float angle, Vector3D center, Vector3D rAxis);	//Rotate around specified center and axis

Matrix4 perspective(float width, float height, float zNear, float zFar);	//Perspective View Matrix

float* value_ptr(Matrix4 mat);		//Returns address of an array that holds all mat4 values
void printMatrix4(Matrix4 mat4);	//Prints out values stored in mat4
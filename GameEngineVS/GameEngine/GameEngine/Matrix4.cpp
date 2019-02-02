#include "Matrix4.h"

Matrix4::Matrix4()
{
	for (int row = 0; row < sizeof(mat4); row++) {
		for (int col = 0; col < sizeof(mat4[0]); col++) {
			mat4[row][col] = 0;
		}
	}
}

void Matrix4::setIdentity()
{
	for (int diag = 0; diag < sizeof(mat4); diag) {
		mat4[diag][diag] = 1;
	}
}

void Matrix4::translate(float x, float y, float z)
{
	mat4[3][0] += x;
	mat4[3][1] += y;
	mat4[3][2] += z;
}

void Matrix4::scale(float x, float y, float z)
{
	mat4[0][0] *= x;
	mat4[1][1] *= y;
	mat4[2][2] *= z;
}

void Matrix4::inverse()
{	
	
}

void Matrix4::transpose()
{
	Matrix4 transpose = Matrix4();
	for (int row = 0; row < sizeof(mat4); row++) {
		for (int col = 0; col < sizeof(mat4[0]); col++) {
			transpose.mat4[col][row] = mat4[row][col];
		}
	}
	for (int row = 0; row < sizeof(mat4); row++) {
		for (int col = 0; col < sizeof(mat4[0]); col++) {
			mat4[row][col] = transpose.mat4[row][col];
		}
	}
	
}

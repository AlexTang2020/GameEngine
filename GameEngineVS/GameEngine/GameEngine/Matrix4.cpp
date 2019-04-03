#define _USE_MATH_DEFINES

#include "Matrix4.h"
#include "Header.h"
#include <cmath>

Matrix4::Matrix4()
{
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			mat4[row][col] = 0.f;
		}
	}
}

Matrix4:: ~Matrix4() {

}


void Matrix4::setIdentity()
{
	for (int diag = 0; diag < 4; diag++) {
		mat4[diag][diag] = 1.f;
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
	float row1I = ( mat4[1][1] * ( (mat4[2][2] * mat4[3][3]) - (mat4[3][2] * mat4[2][3]) ) );
	float row1J = (mat4[1][2] * ((mat4[2][1] * mat4[3][3]) - (mat4[3][1] * mat4[2][3])));
	float row1K = (mat4[1][3] * ((mat4[2][1] * mat4[3][2]) - (mat4[3][1] * mat4[2][2])));
	float row1 = mat4[0][0] * (row1I - row1J + row1K);

	float row2I = (mat4[0][1] * ((mat4[2][2] * mat4[3][3]) - (mat4[3][2] * mat4[2][3])));
	float row2J = (mat4[0][2] * ((mat4[2][1] * mat4[3][3]) - (mat4[3][1] * mat4[2][3])));
	float row2K = (mat4[0][3] * ((mat4[2][1] * mat4[3][2]) - (mat4[3][1] * mat4[2][2])));
	float row2 = mat4[1][0] * (row2I - row2J + row2K);

	float row3I = (mat4[0][1] * ((mat4[1][2] * mat4[3][3]) - (mat4[3][2] * mat4[1][3])));
	float row3J = (mat4[0][2] * ((mat4[1][1] * mat4[3][3]) - (mat4[3][1] * mat4[1][3])));
	float row3K = (mat4[0][3] * ((mat4[1][1] * mat4[3][2]) - (mat4[3][1] * mat4[1][2])));
	float row3 = mat4[2][0] * (row3I - row3J + row3K);

	float row4I = (mat4[0][1] * ((mat4[1][2] * mat4[2][3]) - (mat4[2][2] * mat4[1][3])));
	float row4J = (mat4[0][2] * ((mat4[1][1] * mat4[2][3]) - (mat4[2][1] * mat4[1][3])));
	float row4K = (mat4[0][3] * ((mat4[1][1] * mat4[2][2]) - (mat4[2][1] * mat4[1][2])));
	float row4 = mat4[3][0] * (row4I - row4J + row4K);

	float det = row1 - row2 + row3 - row4;

	float copy[4][4];
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			copy[row][col] = mat4[row][col];
		}
	}

	mat4[0][0] = (row1I - row1J + row1K) / det;

	mat4[0][1] = -((copy[1][0] * copy[2][2] * copy[3][3]) + (copy[1][2] * copy[2][3] * copy[3][0]) + (copy[1][3] * copy[2][0]* copy[3][2])
				- (copy[1][3] * copy[2][2] * copy[3][0]) - (copy[1][2] * copy[2][0] * copy[3][3]) - (copy[1][0] * copy[2][3] * copy[3][2])) / det;

	mat4[0][2] = ((copy[1][0] * copy[2][2] * copy[3][3]) + (copy[1][1] * copy[2][3] * copy[3][0]) + (copy[1][3] * copy[2][0] * copy[3][1])
				- (copy[1][3] * copy[2][1] * copy[3][0]) - (copy[1][1] * copy[2][0] * copy[3][3]) - (copy[1][0] * copy[2][3] * copy[3][1])) / det;

	mat4[0][3] = -((copy[1][0] * copy[2][1] * copy[3][2]) + (copy[1][1] * copy[2][2] * copy[3][0]) + (copy[1][2] * copy[2][0] * copy[3][1])
				- (copy[1][2] * copy[2][1] * copy[3][0]) - (copy[1][1] * copy[2][0] * copy[3][2]) - (copy[1][0] * copy[2][2] * copy[3][1])) / det;


	mat4[1][0] = -(row2I - row2J + row2K) / det;

	mat4[1][1] = ((copy[0][0] * copy[2][2] * copy[3][3]) + (copy[0][2] * copy[2][3] * copy[3][0]) + (copy[0][3] * copy[2][0] * copy[3][2])
				- (copy[0][3] * copy[2][2] * copy[3][0]) - (copy[0][2] * copy[2][0] * copy[3][3]) - (copy[0][0] * copy[2][3] * copy[3][2])) / det;

	mat4[1][2] = -((copy[0][0] * copy[2][1] * copy[3][3]) + (copy[0][1] * copy[2][3] * copy[3][0]) + (copy[0][3] * copy[2][0] * copy[3][1])
				- (copy[0][3] * copy[2][1] * copy[3][0]) - (copy[0][1] * copy[2][0] * copy[3][3]) - (copy[0][0] * copy[2][3] * copy[3][1])) / det;

	mat4[1][3] = ((copy[0][0] * copy[2][1] * copy[3][2]) + (copy[0][1] * copy[2][2] * copy[3][0]) + (copy[0][2] * copy[2][0] * copy[3][1])
				- (copy[0][2] * copy[2][1] * copy[3][0]) - (copy[0][1] * copy[2][0] * copy[3][2]) - (copy[0][0] * copy[2][2] * copy[3][1])) / det;


	mat4[2][0] = (row3I - row3J + row3K) / det;

	mat4[2][1] = -((copy[0][0] * copy[1][2] * copy[3][3]) + (copy[0][2] * copy[1][3] * copy[3][0]) + (copy[0][3] * copy[1][0] * copy[3][2])
				- (copy[0][3] * copy[1][2] * copy[3][0]) - (copy[0][2] * copy[1][0] * copy[3][3]) - (copy[0][0] * copy[1][3] * copy[3][2])) / det;

	mat4[2][2] = ((copy[0][0] * copy[1][1] * copy[3][3]) + (copy[0][1] * copy[1][3] * copy[3][0]) + (copy[0][3] * copy[1][0] * copy[3][1])
				- (copy[0][3] * copy[1][1] * copy[3][0]) - (copy[0][1] * copy[1][0] * copy[3][3]) - (copy[0][0] * copy[1][3] * copy[3][1])) / det;

	mat4[2][3] = -((copy[0][0] * copy[1][1] * copy[3][2]) + (copy[0][1] * copy[1][2] * copy[3][0]) + (copy[0][3] * copy[1][0] * copy[3][1])
				- (copy[0][2] * copy[1][1] * copy[3][0]) - (copy[0][1] * copy[1][0] * copy[3][2]) - (copy[0][0] * copy[1][2] * copy[3][1])) / det;


	mat4[3][0] = -(row4I - row4J + row4K) / det;

	mat4[3][1] = ((copy[0][0] * copy[1][2] * copy[2][3]) + (copy[0][2] * copy[1][3] * copy[2][0]) + (copy[0][3] * copy[1][0] * copy[2][2])
				- (copy[0][3] * copy[1][2] * copy[2][0]) - (copy[0][2] * copy[1][0] * copy[2][3]) - (copy[0][0] * copy[1][3] * copy[2][2])) / det;

	mat4[3][2] = -((copy[0][0] * copy[1][1] * copy[2][3]) + (copy[0][1] * copy[1][3] * copy[2][0]) + (copy[0][3] * copy[1][0] * copy[2][1])
				- (copy[0][3] * copy[1][1] * copy[2][0]) - (copy[0][1] * copy[1][0] * copy[2][3]) - (copy[0][0] * copy[1][3] * copy[2][1])) / det;

	mat4[3][3] = ((copy[0][0] * copy[1][1] * copy[2][2]) + (copy[0][1] * copy[1][2] * copy[2][0]) + (copy[0][2] * copy[1][0] * copy[2][1])
				- (copy[0][2] * copy[1][1] * copy[2][0]) - (copy[0][1] * copy[1][0] * copy[2][2]) - (copy[0][0] * copy[1][2] * copy[2][1])) / det;

	transpose();
}

void Matrix4::transpose()
{
	Matrix4 transpose = Matrix4();
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			transpose.mat4[col][row] = mat4[row][col];
		}
	}
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4;  col++) {
			mat4[row][col] = transpose.mat4[row][col];
		}
	}
	
}

void Matrix4::rotateX(float angle)
{
	mat4[1][1] *= (float) cos(angle*M_PI/180.f);
	mat4[1][2] *= (float) sin(angle*M_PI/180.f);
	mat4[2][1] *= (float) -sin(angle*M_PI / 180.f);
	mat4[2][2] *= (float) cos(angle*M_PI / 180.f);
}

void Matrix4::rotateY(float angle)
{
	mat4[0][0] *= (float) cos(angle*M_PI / 180.f);
	mat4[0][2] *= (float) -sin(angle*M_PI / 180.f);
	mat4[2][0] *= (float) sin(angle*M_PI / 180.f);
	mat4[2][2] *= (float) cos(angle*M_PI / 180.f);
}

void Matrix4::rotateZ(float angle)
{
	mat4[0][0] *= (float) cos(angle*M_PI / 180.f);
	mat4[0][1] *= (float) sin(angle*M_PI / 180.f);
	mat4[1][0] *= (float)-sin(angle*M_PI / 180.f);
	mat4[1][1] *= (float) cos(angle*M_PI / 180.f);
}

void Matrix4::concatenate(Matrix4 & right)
{
	Matrix4 copy;

	for (int i = 0; i < 4; i++) {
		copy.mat4[0][0] += (mat4[0][i] * right.mat4[i][0]);
		copy.mat4[0][1] += (mat4[0][i] * right.mat4[i][1]);
		copy.mat4[0][2] += (mat4[0][i] * right.mat4[i][2]);
		copy.mat4[0][3] += (mat4[0][i] * right.mat4[i][3]);

		copy.mat4[1][0] += (mat4[1][i] * right.mat4[i][0]);
		copy.mat4[1][1] += (mat4[1][i] * right.mat4[i][1]);
		copy.mat4[1][2] += (mat4[1][i] * right.mat4[i][2]);
		copy.mat4[1][3] += (mat4[1][i] * right.mat4[i][3]);

		copy.mat4[2][0] += (mat4[2][i] * right.mat4[i][0]);
		copy.mat4[2][1] += (mat4[2][i] * right.mat4[i][1]);
		copy.mat4[2][2] += (mat4[2][i] * right.mat4[i][2]);
		copy.mat4[2][3] += (mat4[2][i] * right.mat4[i][3]);

		copy.mat4[3][0] += (mat4[3][i] * right.mat4[i][0]);
		copy.mat4[3][1] += (mat4[3][i] * right.mat4[i][1]);
		copy.mat4[3][2] += (mat4[3][i] * right.mat4[i][2]);
		copy.mat4[3][3] += (mat4[3][i] * right.mat4[i][3]);
	}
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			mat4[row][col] = copy.mat4[row][col];
		}
	}
}

float* value_ptr(Matrix4 mat) {
	float arr[16];
	int i = 0;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			arr[i] = mat.mat4[row][col];
			i++;
		}
	}
	return &arr[0];
}

void printMatrix4(Matrix4 matrix){
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			std::cout << matrix.mat4[row][col] << " ";
		}
		std::cout << "\n";
	}
}

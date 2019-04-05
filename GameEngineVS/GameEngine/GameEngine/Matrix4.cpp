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

Matrix4 translate(float x, float y, float z)
{
	Matrix4 mTrans = Matrix4();
	mTrans.setIdentity();
	mTrans.mat4[3][0] = x;
	mTrans.mat4[3][1] = y;
	mTrans.mat4[3][2] = z;
	return mTrans;
}

Matrix4 translate(Vector3D vec) {
	Martrix4 mTrans = Matrix4();
	mTrans.setIdentity();
	mTrans.mat4[3][0] = vec.x;
	mTrans.mat4[3][1] = vec.y;
	mTrans.mat4[3][2] = vec.z;
	return mTrans;
}

Matrix4 scale(float x, float y, float z)
{
	Matrix4 mScale = Matrix4();
	mScale.setIdentity();
	mScale.mat4[0][0] *= x;
	mScale.mat4[1][1] *= y;
	mScale.mat4[2][2] *= z;
	return mScale;
}

Matrix4 scale(float val)
{
	Matrix4 mScale = Matrix4();
	mScale.setIdentity();
	mScale.mat4[0][0] *= val;
	mScale.mat4[1][1] *= val;
	mScale.mat4[2][2] *= val;
	return mScale;
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

Matrix4 rotate(float angle, float x, float y, float z) {
	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - c;
	Vector3D rAxis = Vector3D(x,y,z);
	Vector3D rNormal = rAxis.Normal();
	float xN = rNormal.x;
	float yN = rNormal.y;
	float zN = rNormal.z;

	Matrix4 rMat = Matrix4();
	rMat.mat4[0][0] = 1 + t * (xN*xN - 1);
	rMat.mat4[0][1] = zN * s + t * xN*yN;
	rMat.mat4[0][2] = -yN * s + t * xN*zN;
	rMat.mat4[0][3] = 0.0f;

	rMat.mat4[1][0] = -zN * s + t * xN*yN;
	rMat.mat4[1][1] = 1 + t * (yN*yN - 1);
	rMat.mat4[1][2] = xN * s + t * yN*zN;
	rMat.mat4[1][3] = 0.0f;

	rMat.mat4[2][0] = yN * s + t * xN*zN;
	rMat.mat4[2][1] = -xN * s + t * yN*zN;
	rMat.mat4[2][2] = 1 + t * (zN*zN - 1);
	rMat.mat4[2][3] = 0.0f;

	rMat.mat4[3][0] = 0.0f;
	rMat.mat4[3][1] = 0.0f;
	rMat.mat4[3][2] = 0.0f;
	rMat.mat4[3][3] = 1.0f;

	return rMat;
}

Matrix4 rotateX(float angle)
{
	Matrix4 mRotate = Matrix4();
	mRotate.setIdentity();
	mRotate.mat4[1][1] = cosf(angle);
	mRotate.mat4[1][2] = sinf(angle);
	mRotate.mat4[2][1] =-sinf(angle);
	mRotate.mat4[2][2] = cosf(angle);
	return mRotate;
}

Matrix4 rotateY(float angle)
{
	Matrix4 mRotate = Matrix4();
	mRotate.setIdentity();
	mRotate.mat4[0][0] = cosf(angle);
	mRotate.mat4[0][2] =-sinf(angle);
	mRotate.mat4[2][0] = sinf(angle);
	mRotate.mat4[2][2] = cosf(angle);
	return mRotate;

}

Matrix4 rotateZ(float angle)
{
	Matrix4 mRotate = Matrix4();
	mRotate.setIdentity();
	mRotate.mat4[0][0] =  cosf(angle);
	mRotate.mat4[0][1] =  sinf(angle);
	mRotate.mat4[1][0] = -sinf(angle);
	mRotate.mat4[1][1] = cosf(angle);
	return mRotate;
}

Matrix4 rotateAtCenter(float angle, Vector3D center, Vector3D rAxis) {
	return translate(center*-1).concatenate(rotate(rAxis, angle).concatenate(translate(center)));
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

Matrix4 Matrix4::perspective(float width, float height, float zNear, float zFar) {
	Matrix4 pMat = Matrix4();
	pMat.setIdentity();
	pMat.mat4[0][0] = 2.0f * zNear / width;
	pMat.mat4[1][0] = 0.0f;
	pMat.mat4[2][0] = 0.0f;
	pMat.mat4[3][0] = 0.0f;

	pMat.mat4[0][1] = 0.0f;
	pMat.mat4[1][1] = 2.0f * zNear / height;
	pMat.mat4[2][1] = 0.0f;
	pMat.mat4[3][1] = 0.0f;

	pMat.mat4[0][2] = 0.0f;
	pMat.mat4[1][2] = 0.0f;
	pMat.mat4[2][2] = zFar / (zNear - zFar);
	pMat.mat4[3][2] = zFar * zNear / (zNear - zFar);

	pMat.mat4[0][3] = 0.0f;
	pMat.mat4[1][3] = 0.0f;
	pMat.mat4[2][3] = -1.0f;
	pMat.mat4[3][3] = 0.0f;
	return pMat;
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

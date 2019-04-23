#define _USE_MATH_DEFINES

#include "Matrix4.h"
#include <cmath>

Matrix4::Matrix4()
{
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			mat4[row][col] = 0.0f;
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

Matrix4 translate(Matrix4 mat, float x, float y, float z)
{
	Matrix4 mTrans = Matrix4();
	mTrans.setIdentity();
	mTrans.mat4[3][0] += x;
	mTrans.mat4[3][1] += y;
	mTrans.mat4[3][2] += z;
	Matrix4 result = mat.concatenate(mTrans);
	return result;
}

/*
Matrix4 translateVec(Vector3D vec) {
	return translate(vec.x, vec.y, vec.z);
}
*/

Matrix4 scale(Matrix4 mat, float x, float y, float z)
{
	Matrix4 mScale = Matrix4();
	mScale.setIdentity();
	mScale.mat4[0][0] *= x;
	mScale.mat4[1][1] *= y;
	mScale.mat4[2][2] *= z;
	Matrix4 result = mat.concatenate(mScale);
	return result;
}

/*
Matrix4 scaleUniform(float val)
{
	return scale(val, val, val);
}
*/

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

Matrix4 rotate(Matrix4 mat, float angle, float x, float y, float z) {
	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - c;
	Vector3D rAxis = Vector3D(x,y,z);
	Vector3D rNormal = rAxis.Normal();
	float xN = rNormal.x;
	float yN = rNormal.y;
	float zN = rNormal.z;

	Matrix4 rMat = Matrix4();
	rMat.setIdentity();
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

	Matrix4 result = mat.concatenate(rMat);

	return result;
}

/*
Matrix4 rotateVec(float angle, Vector3D rAxis) {
	return rotate(angle, rAxis.x, rAxis.y, rAxis.z);
}
*/

Matrix4 rotateX(Matrix4 mRotate, float angle)
{
	mRotate.mat4[1][1] = cosf(angle);
	mRotate.mat4[1][2] = sinf(angle);
	mRotate.mat4[2][1] =-sinf(angle);
	mRotate.mat4[2][2] = cosf(angle);
	return mRotate;
}

Matrix4 rotateY(Matrix4 mRotate, float angle)
{
	mRotate.mat4[0][0] = cosf(angle);
	mRotate.mat4[0][2] =-sinf(angle);
	mRotate.mat4[2][0] = sinf(angle);
	mRotate.mat4[2][2] = cosf(angle);
	return mRotate;

}

Matrix4 rotateZ(Matrix4 mRotate, float angle)
{
	mRotate.mat4[0][0] =  cosf(angle);
	mRotate.mat4[0][1] =  sinf(angle);
	mRotate.mat4[1][0] = -sinf(angle);
	mRotate.mat4[1][1] = cosf(angle);
	return mRotate;
}

/*
Matrix4 rotateAtCenter(Matrix4 mRotate, float angle, Vector3D center, Vector3D rAxis) {
	Vector3D inVec = center * -1;
	Matrix4 invTrans = translate(mRotate, inVec.x, inVec.y, inVec.z);
	Matrix4 rotation = rotate(mRotate, angle, rAxis.x, rAxis.y, rAxis.z);
	Matrix4 trans = translate(mRotate, center.x, center.y, center.z);
	return rotation.concatenate(trans);
}

Matrix4 rotateAtMat(Matrix4 mRotate, float angle, Matrix4 trans, Vector3D rAxis)
{
	Matrix4 rotation = rotate(mRotate, angle, rAxis.x, rAxis.y, rAxis.z);
	return trans.concatenate(rotation);
}
*/

Vector3D concat(Vector3D left, Matrix4 &right)
{
	float vx = left.x;
	float vy = left.y;
	float vz = left.z;
	int vw = left.w;

	float x = vx * right.mat4[0][0] + vy * right.mat4[1][0] + vz * right.mat4[2][0] + vw * right.mat4[3][0];
	float y = vx * right.mat4[0][1] + vy * right.mat4[1][1] + vz * right.mat4[2][1] + vw * right.mat4[3][1];
	float z = vx * right.mat4[0][2] + vy * right.mat4[1][2] + vz * right.mat4[2][2] + vw * right.mat4[3][2];
	int w = vx * right.mat4[0][3] + vy * right.mat4[1][3] + vz * right.mat4[2][3] + vw * right.mat4[3][3];
	return Vector3D(x, y, z, w);
}

Matrix4 Matrix4::concatenate(Matrix4 & right)
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
	/*
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			mat4[row][col] = copy.mat4[row][col];
		}
	}
	*/
	return copy;
}

Matrix4 Matrix4::rotateConcat(Matrix4 mat, float angle, float x, float y, float z)
{
	Matrix4 rot = rotate(mat, angle, x, y, z);
	return concatenate(rot);
}

Matrix4 perspective(float fov, float aspect, float zNear, float zFar){	

	float yScale = 1.0 / tan(fov / 2);
	float xScale = yScale / aspect;
	float nearFar = zNear - zFar;

	Matrix4 pMat = Matrix4();
	pMat.setIdentity();
	pMat.mat4[0][0] = xScale;
	pMat.mat4[1][0] = 0.0f;
	pMat.mat4[2][0] = 0.0f;
	pMat.mat4[3][0] = 0.0f;

	pMat.mat4[0][1] = 0.0f;
	pMat.mat4[1][1] = yScale;
	pMat.mat4[2][1] = 0.0f;
	pMat.mat4[3][1] = 0.0f;

	pMat.mat4[0][2] = 0.0f;
	pMat.mat4[1][2] = 0.0f;
	pMat.mat4[2][2] = (zFar + zNear) / nearFar;
	pMat.mat4[3][2] = 2 * zFar * zNear / nearFar;

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

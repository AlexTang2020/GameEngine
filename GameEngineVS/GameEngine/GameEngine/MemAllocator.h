#pragma once
#include "Manager.h"
#include "Math.h"

class MemAllocator {
public:
	//Stores elements of that data type into a vector
	std::vector<Vector3D> vecMemory;
	std::vector<Point3D> posMemory;
	std::vector<Quaternion> quatMemory;
	std::vector<Matrix4> matMemory;

	//Stores addresses for respective data types in a vector
	std::vector<Vector3D*> vecAddr;
	std::vector<Point3D*> posAddr;
	std::vector<Quaternion*> quatAddr;
	std::vector<Matrix4*> matAddr;

	int vSize;
	int pSize;
	int qSize;
	int mSize;

	explicit MemAllocator(int vecSize, int posSize, int quatSize, int matSize);

	Vector3D* vecAlloc();		//return address of free vector
	Point3D* posAlloc();		//return address of free point
	Quaternion* quatAlloc();	//return address of free quaternion
	Matrix4* matAlloc();		//return address of matrix

	void vecFree(Vector3D vec);		//push address of vector back to pool
	void posFree(Point3D pos);		//push address of point back to pool 
	void quatFree(Quaternion quat);	//push address of quaternion back to pool
	void matFree(Matrix4 mat);		//push address of matrix back to pool

	void resetAll();	//free all memory

private:
	
};
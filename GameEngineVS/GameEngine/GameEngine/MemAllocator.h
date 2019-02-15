#pragma once
#include "Header.h"

class MemAllocator {
public:
	std::vector<Vector3D> vecMemory;
	std::vector<Point3D> posMemory;
	std::vector<Quaternion> quatMemory;
	std::vector<Matrix4> matMemory;

	std::vector<Vector3D*> vecAddr;
	std::vector<Point3D*> posAddr;
	std::vector<Quaternion*> quatAddr;
	std::vector<Matrix4*> matAddr;

	int vSize;
	int pSize;
	int qSize;
	int mSize;

	explicit MemAllocator(int vecSize, int posSize, int quatSize, int matSize);

	Vector3D* vecAlloc();
	Point3D* posAlloc();
	Quaternion* quatAlloc();
	Matrix4* matAlloc();

	void vecFree(Vector3D vec);
	void posFree(Point3D pos);
	void quatFree(Quaternion quat);
	void matFree(Matrix4 mat);

	void resetAll();

private:
	
};
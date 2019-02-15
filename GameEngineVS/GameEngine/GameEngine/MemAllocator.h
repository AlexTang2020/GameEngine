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

	explicit MemAllocator(int vecSize, int posSize, int quatSize, int matSize);

	void vecAlloc();
	void posAlloc();
	void quatAlloc();
	void matAlloc();

	void vecFree();
	void posFree();
	void quatFree();
	void matFree();

	void resetAll();

private:
	
};
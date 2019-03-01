#include "MemAllocator.h"


MemAllocator::MemAllocator(int vecSize, int posSize, int quatSize, int matSize) {
	vSize = vecSize;
	pSize = posSize;
	qSize = quatSize;
	mSize = matSize;

	for (int i = 0; i < vecSize; i++) {
		vecMemory.push_back(Vector3D());
		vecAddr.push_back(&vecMemory[i]);
	}
	for (int i = 0; i < posSize; i++) {
		posMemory.push_back(Point3D());
		posAddr.push_back(&posMemory[i]);
	}
	for (int i = 0; i < quatSize; i++) {
		quatMemory.push_back(Quaternion());
		quatAddr.push_back(&quatMemory[i]);
	}
	for (int i = 0; i < matSize; i++) {
		matMemory.push_back(Matrix4());
		matAddr.push_back(&matMemory[i]);
	}
}

Vector3D* MemAllocator::vecAlloc() {
	if (!vecMemory.empty()) {
		Vector3D* myVector = vecAddr.back();
		vecAddr.pop_back();
		return myVector;
	}
	return nullptr;
}
Point3D* MemAllocator::posAlloc() {
	if (!posMemory.empty()) {
		Point3D* myPoint = posAddr.back();
		posAddr.pop_back();
		return myPoint;
	}
	return nullptr;
}
Quaternion* MemAllocator::quatAlloc() {
	if (!quatMemory.empty()) {
		Quaternion* myQuaternion = quatAddr.back();
		quatAddr.pop_back();
		return myQuaternion;
	}
	return nullptr;
}
Matrix4* MemAllocator::matAlloc() {
	if (!matMemory.empty()) {
		Matrix4* myMatrix = matAddr.back();
		matAddr.pop_back();
		return myMatrix;
	}
	return nullptr;
}


void MemAllocator::vecFree(Vector3D vec) {
	if (vecAddr.size() < vSize) {
		vecAddr.push_back(&vec);
	}
}
void MemAllocator::posFree(Point3D pos) {
	if (posAddr.size() < pSize) {
		posAddr.push_back(&pos);
	}
}
void MemAllocator::quatFree(Quaternion quat) {
	if (quatAddr.size() < qSize) {
		quatAddr.push_back(&quat);
	}
}
void MemAllocator::matFree(Matrix4 mat) {
	
	if (matAddr.size() < mSize) {
		matAddr.push_back(&mat);
	}
}


void MemAllocator::resetAll() {
	while (vecAddr.size() < vSize) {

	}
	while (posAddr.size() < pSize) {

	}
	while (quatAddr.size() < qSize) {

	}
	while (matAddr.size() < mSize) {

	}
}

#include "MemAllocator.h"


MemAllocator::MemAllocator(int vecSize, int posSize, int quatSize, int matSize) {
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

void MemAllocator::vecAlloc() {

}
void MemAllocator::posAlloc() {

}
void MemAllocator::quatAlloc() {

}
void MemAllocator::matAlloc() {

}


void MemAllocator::vecFree() {

}
void MemAllocator::posFree() {

}
void MemAllocator::quatFree() {

}
void MemAllocator::matFree() {

}


void MemAllocator::resetAll() {

}

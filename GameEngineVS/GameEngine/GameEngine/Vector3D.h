#pragma once
#include <math.h>

class Vector3D
{
public:
	float x = 0;
	float y = 0;
	float z = 0;
	int w = 0;

	Vector3D();
	explicit Vector3D(float x, float y, float z, int w = 0);

	float Magnitude() const;		//gets the magnitude

	void Normalize();		//Normalizes vector

	Vector3D Normal() const; 	//returns a Vector3 that is the normal, but doesn't change the original one

	// member functions
	Vector3D operator+(Vector3D const& right);	//Return sum of two vectors
	Vector3D operator-(Vector3D const& right);	//Return difference of two vectors
	Vector3D operator*(float val);				//Return vector scaled by a value

	void add(Vector3D const& right);			//Add a vector to the current vector
	void scale(float valx, float valy, float valz);//Scale the current vector by some x,y,z values

	float Dot(Vector3D const& right);			//Return dot product of two vectors
	Vector3D Cross(Vector3D const& right);		//Return cross product of two vectors

	Vector3D Lerp(Vector3D& left, float val);	//Return linear interpolation of two vectors
private:

};

// free standing functions
float Dot(Vector3D const & right, Vector3D const & left);		//Return dot product of two vectors
Vector3D Cross(Vector3D const & left, Vector3D const & right);	//Return cross product of two vectors

Vector3D Lerp(Vector3D & left, Vector3D & right, float val);	//Return linear interpolation of two vectors

// assuming right handed Y - up axis
static const Vector3D VECTOR3D_UP{ 0.0f, 1.0f, 0.0f};
static const Vector3D VECTOR3D_DOWN{ 0.0f, -1.0f, 0.0f};
static const Vector3D VECTOR3D_RIGHT{ 1.0f, 0.0f, 0.0f};
static const Vector3D VECTOR3D_LEFT{ -1.0f, 1.0f, 0.0f};
static const Vector3D VECTOR3D_FORWARD{ 0.0f, 0.0f, 1.0f};
static const Vector3D VECTOR3D_BACKWARD{ 0.0f, 0.0f, -1.0f};
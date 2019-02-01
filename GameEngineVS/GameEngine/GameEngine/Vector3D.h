#pragma once

class Vector3D
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3D();

	explicit Vector3D(float x, float y, float z);

	//gets the magnitude
	float Magnitude() const;

	//mutates the class
	void Normalize();

	//returns a Vector3 that is the normal, but doesn't change the original one
	Vector3D Normal() const;

	// member functions
	Vector3D operator+(Vector3D const& right);
	Vector3D operator*(float val);

	void add(Vector3D const& right);
	void scale(float val);

	float Dot(Vector3D const& right);
	Vector3D Cross(Vector3D const& right);

	Vector3D Lerp(Vector3D& left, float val);

private:

};

// free standing functions
float Dot(Vector3D const & right, Vector3D const & left);
Vector3D Cross(Vector3D const & left, Vector3D const & right);

Vector3D Lerp(Vector3D & left, Vector3D & right, float val);

// assuming right handed Y - up axis
static const Vector3D VECTOR3D_UP{ 0.0f, 1.0f, 0.0f };
static const Vector3D VECTOR3D_DOWN{ 0.0f, -1.0f, 0.0f };
static const Vector3D VECTOR3D_RIGHT{ 1.0f, 0.0f, 0.0f };
static const Vector3D VECTOR3D_LEFT{ -1.0f, 1.0f, 0.0f };
static const Vector3D VECTOR3D_FORWARD{ 0.0f, 0.0f, 1.0f };
static const Vector3D VECTOR3D_BACKWARD{ 0.0f, 0.0f, -1.0f };
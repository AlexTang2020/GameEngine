#pragma once

class Quaternion
{
public:
	float qx = 0;
	float qy = 0;
	float qz = 0;
	float qw = 0;

	Quaternion();

	explicit Quaternion(float qx, float qy, float qz, float qw);

	// member functions
	Quaternion operator+(Quaternion const& right);
	Quaternion operator-(Quaternion const& right);
	Quaternion operator*(Quaternion const& right);

	Quaternion operator+=(Quaternion const& right);
	Quaternion operator-=(Quaternion const& right);
	Quaternion operator*=(Quaternion const& right);

	Quaternion scale(float val);
};
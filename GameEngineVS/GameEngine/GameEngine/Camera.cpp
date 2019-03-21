#define _USE_MATH_DEFINES

#include "Camera.h"
Camera::Camera()
{
}

Camera::~Camera()
{
}

// Constructor with vectors
Camera::Camera(Vector3D position, Vector3D up, float yaw, float pitch) : Front(Vector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

// Constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(Vector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = Vector3D(posX, posY, posZ);
	WorldUp = Vector3D(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Matrix4 Camera::GetViewMatrix()
{
	return lookAt(Position, Position + Front, Up);
}

Matrix4 Camera::lookAt(Vector3D eye, Vector3D target, Vector3D up)
{
	// compute the forward vector from target to eye
	Vector3D forward = eye - target;
	forward.Normalize();                 // make unit length

	// compute the left vector
	Vector3D left = up.Cross(forward); // cross product
	left.Normalize();

	// recompute the orthonormal up vector
	Vector3D up = forward.Cross(left);    // cross product

	// init 4x4 matrix
	Matrix4 matrix;
	matrix.setIdentity();

	// set rotation part, inverse rotation matrix: M^-1 = M^T for Euclidean transform
	matrix.mat4[0][0] = left.x;
	matrix.mat4[0][1] = left.y;
	matrix.mat4[0][2] = left.z;

	matrix.mat4[1][0] = up.x;
	matrix.mat4[1][1] = up.y;
	matrix.mat4[1][2] = up.z;
	
	matrix.mat4[2][0] = forward.x;
	matrix.mat4[2][1] = forward.y;
	matrix.mat4[2][2] = forward.z;

	// set translation part
	matrix.mat4[0][3] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
	matrix.mat4[1][3] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
	matrix.mat4[2][3] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;

	return matrix;
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position.add(Front * velocity);
	if (direction == BACKWARD)
		Position.add(Front * -1.f * velocity);
	if (direction == LEFT)
		Position.add(Right * -1.f * velocity);
	if (direction == RIGHT)
		Position.add(Right * velocity);
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	Vector3D front;
	front.x = cos(Yaw * (M_PI/180.f)) * cos(Pitch * (M_PI / 180.f));
	front.y = sin((Pitch) * (M_PI / 180.f));
	front.z = sin((Yaw) * (M_PI / 180.f)) * cos((Pitch) * (M_PI / 180.f));
	Front = front.Normal();
	// Also re-calculate the Right and Up vector
	Right = (Cross(Front, WorldUp)).Normal();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = (Cross(Right, Front)).Normal();
}


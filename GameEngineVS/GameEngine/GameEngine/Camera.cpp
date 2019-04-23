#define _USE_MATH_DEFINES

#include "Camera.h"
Camera::Camera()
{
	Position = Vector3D(0.0f,0.0f,0.0f);
	WorldUp = Vector3D(0.0f, 1.0f, 0.0f);
	Up = Vector3D(0.0f, 1.0f, 0.0f);
	Front = Vector3D(0.0f,0.0f,-1.0f);
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Pitch = PITCH;
	Yaw = YAW;
	Zoom = ZOOM;
	updateCameraVectors();
}

Camera::~Camera()
{
}

// Constructor with vectors
Camera::Camera(Vector3D position, Vector3D wUp, float yaw, float pitch) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = wUp;
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
	return lookAt(Position, Position + Front, WorldUp);
}

Matrix4 Camera::lookAt(Vector3D eye, Vector3D target, Vector3D up)
{
	// compute the forward vector from target to eye
	Vector3D forward = eye - target;
	forward.Normalize();                 // make unit length

	// compute the left vector
	Vector3D upNorm = up.Normal();
	Vector3D left = upNorm.Cross(forward); // cross product
	left.Normalize();

	// recompute the orthonormal up vector
	Vector3D Up = forward.Cross(left);    // cross product
	
	Matrix4 translation = Matrix4(); 
	translation.setIdentity();
	translation.mat4[3][0] = eye.x; // Third column, first row
	translation.mat4[3][1] = eye.y;
	translation.mat4[3][2] = eye.z;

	Matrix4 rotation = Matrix4();
	rotation.setIdentity();
	rotation.mat4[0][0] = left.x; // First column, first row
	rotation.mat4[1][0] = left.y;
	rotation.mat4[2][0] = left.z;
	rotation.mat4[0][1] = Up.x; // First column, second row
	rotation.mat4[1][1] = Up.y;
	rotation.mat4[2][1] = Up.z;
	rotation.mat4[0][2] = forward.x; // First column, third row
	rotation.mat4[1][2] = forward.y;
	rotation.mat4[2][2] = forward.z;
	
	return translation.concatenate(rotation);
	
	/*
	// init 4x4 matrix
	Matrix4 matrix;
	matrix.setIdentity();

	// set rotation part, inverse rotation matrix: M^-1 = M^T for Euclidean transform
	matrix.mat4[0][0] = left.x;
	matrix.mat4[1][0] = left.y;
	matrix.mat4[2][0] = left.z;

	matrix.mat4[0][1] = Up.x;
	matrix.mat4[1][1] = Up.y;
	matrix.mat4[2][1] = Up.z;
	
	matrix.mat4[0][2] = forward.x;
	matrix.mat4[1][2] = forward.y;
	matrix.mat4[2][2] = forward.z;

	// set translation part
	matrix.mat4[3][0] = -(-left.x * eye.x - left.y * eye.y - left.z * eye.z);
	matrix.mat4[3][1] = -(-Up.x * eye.x - Up.y * eye.y - Up.z * eye.z);
	matrix.mat4[3][2] = -(-forward.x * eye.x - forward.y * eye.y - forward.z * eye.z);

	return matrix;
	*/
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(int direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == 0)
		Position.add(Front * velocity);
	if (direction == 1)
		Position.add(Front * -1.f * velocity);
	if (direction == 2)
		Position.add(Right * -1.f * velocity);
	if (direction == 3)
		Position.add(Right * velocity);
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch -= yoffset;

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
	front.x = (float) cos(Yaw * (M_PI/180.f)) * (float)cos(Pitch * (M_PI / 180.f));
	front.y = (float) sin((Pitch) * (M_PI / 180.f));
	front.z = (float) sin((Yaw) * (M_PI / 180.f)) * (float)cos((Pitch) * (M_PI / 180.f));
	Front = front.Normal();
	// Also re-calculate the Right and Up vector
	Right = (Cross(Front, WorldUp)).Normal();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = (Cross(Right, Front)).Normal();
}

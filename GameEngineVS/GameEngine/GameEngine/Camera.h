#pragma once
#include "Math.h"
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	~Camera();
	Camera(Vector3D position, Vector3D wUp, float yaw, float pitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// Camera Attributes
	Vector3D Position;
	Vector3D Front;
	Vector3D Up;
	Vector3D Right;
	Vector3D WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	
	Matrix4 GetViewMatrix();
	Matrix4 lookAt(Vector3D eye, Vector3D target, Vector3D up);
	void ProcessKeyboard(int direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);


private:
	void updateCameraVectors();
};


// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

/*
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
static enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};*/
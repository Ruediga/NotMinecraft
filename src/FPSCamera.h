#pragma once

// camera by "www.learnopengl.com"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera
{
public:
	enum class Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = -90.0f, float _pitch = 0.0f)
		: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f)
	{
		position = _position;
		worldUp = _up;
		yaw = _yaw;
		pitch = _pitch;
		updateCameraVectors();
	}

	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(position, position + front, up);
	}

	void updateMovement(Camera::Movement direction, float dt)
	{
		if (triple_speed_enabled)
			movementSpeed = 7.5f;
		else movementSpeed = 2.5f;

		float velocity = movementSpeed * dt;

		switch (direction)
		{
		case (Movement::FORWARD): {
			position += front * velocity;
			break;
		}
		case (Movement::BACKWARD): {
			position -= front * velocity;
			break;
		}
		case (Movement::LEFT): {
			position -= right * velocity;
			break;
		}
		case (Movement::RIGHT): {
			position += right * velocity;
			break;
		}
		case (Movement::UP): {
			position += worldUp * velocity;
			break;
		}
		case (Movement::DOWN): {
			position -= worldUp * velocity;
			break;
		}
		}
	}

	void updateView(float x_offset, float y_offset, GLboolean constrainPitch = true)
	{
		x_offset *= mouseSensitivity;
		y_offset *= mouseSensitivity;

		yaw += x_offset;
		pitch += y_offset;

		if (constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateCameraVectors();
	}

	const glm::vec3& getNormalizedDirectionVector()
	{
		return front;
	}

	float getZoom() { return zoom; }

	bool triple_speed_enabled;
	glm::vec3 position;

private:
	// camera attributes
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	// euler angles
	float yaw;
	float pitch;
	// camera settings
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	void updateCameraVectors()
	{
		glm::vec3 new_front{};
		new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		new_front.y = sin(glm::radians(pitch));
		new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(new_front);
		right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
		up = glm::normalize(glm::cross(right, front));
	}
};
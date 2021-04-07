#include "Camera.hpp"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera() :
	positionVector		(0.0f, 0.0f, 6.0f),
	targetVector  		(0.0f, 0.0f, 0.0f),
	orientationVector	(0.0f, 1.0f, 0.0f),
	viewHasChanged(true)
{}

void Camera::setPosition(glm::vec3 argPosition)
{
	positionVector = argPosition;
	viewHasChanged = true;
}

void Camera::setPosition(float x, float y, float z)
{
	positionVector = glm::vec3(x, y, z);
	viewHasChanged = true;
}

glm::mat4 Camera::viewMatrix()
{
	if(viewHasChanged)
	{
		m_viewMatrix = glm::lookAt(	this->positionVector,
									this->targetVector,
									this->orientationVector );

		viewHasChanged = false;
	}

	return m_viewMatrix;
}

Camera camera;

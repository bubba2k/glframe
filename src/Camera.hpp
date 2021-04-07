#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
	friend class Renderer;

	glm::vec3 positionVector, targetVector, orientationVector;
	glm::mat4 m_viewMatrix;

	glm::mat4 viewMatrix();
	bool viewHasChanged;

public:
	Camera();

	void setPosition(glm::vec3);
	void setPosition(float, float, float);

};

extern Camera camera;

#endif

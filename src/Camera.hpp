#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Camera
{
	void setPosition(glm::vec3);
	void setPosition(float, float, float);

	// TODO: implement functions below
	void offsetPosition(glm::vec3);
	void offsetPosition(float, float, float);
	void lookAt(glm::vec3);
	void lookAt(float, float, float);
	void rotate(float, float, float);
	glm::mat4 viewMatrix();
};

#endif

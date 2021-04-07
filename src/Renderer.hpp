#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glm/gtc/matrix_transform.hpp>

#include "Tracker.hpp"

class Renderer
{
	friend class Display;

	glm::mat4 m_viewMatrix, m_projectionMatrix;
	bool viewHasChanged, projectionHasChanged;

	float _aspectRatio;

public:
	Renderer();

	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix();

	void renderScene();
};

extern Renderer MeshRenderer;

#endif

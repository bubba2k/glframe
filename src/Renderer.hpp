#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
	friend class Display;

	Renderer();

	static float aspectRatio;
	static glm::mat4 m_viewMatrix, m_projectionMatrix;
	static bool viewHasChanged, projectionHasChanged;

public:
	static bool init(float argAspectRatio);

	static glm::mat4 viewMatrix();
	static glm::mat4 projectionMatrix();

	static void renderScene();
};

#endif

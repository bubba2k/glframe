#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glframe.hpp"

class Renderer
{
	glm::mat4 viewMatrix, projectionMatrix;

public:
	void renderMesh(Mesh &mesh);
};

#endif

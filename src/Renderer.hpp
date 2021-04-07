#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glframe.hpp"

template <class T>
class Tracker : public std::vector<T>
{

public:
	int  track(T);
	void forget(int);
};

class Renderer
{
	glm::mat4 m_viewMatrix, m_projectionMatrix;
	bool viewHasChanged, projectionHasChanged;

public:
	Renderer();

	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix();

	void renderScene();
};


extern Renderer MeshRenderer;
extern Tracker<Mesh *> MeshTracker;

#endif

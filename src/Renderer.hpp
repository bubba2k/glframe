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


extern Renderer MeshRenderer;
extern Tracker<Mesh *> MeshTracker;
extern Camera camera;

#endif

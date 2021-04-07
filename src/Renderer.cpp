#include "Renderer.hpp"


Renderer::Renderer() :
	projectionHasChanged(true)
{}

glm::mat4 Renderer::projectionMatrix()
{
	if(projectionHasChanged)
	{
		m_projectionMatrix = glm::perspective(	glm::radians(60.0f),	// Vertical FOV
												16.0f/9.0f,				// Aspect Ratio
												0.01f,					// Near Clipping Plane
												100.0f	);				// Far  Clipping Plane
		projectionHasChanged = false;
	}

	return m_projectionMatrix;
}

void Renderer::renderScene()
{
	std::vector<Mesh *>::iterator itMeshes = MeshTracker.begin();
	for( ; itMeshes < MeshTracker.end(); itMeshes++)
	{
		if(*itMeshes != nullptr)
		{
			auto &mesh = **itMeshes;

			// Create and send MVP Matrix
			glm::mat4 mvpMatrix = this->projectionMatrix() * camera.viewMatrix() *  mesh.transformationMatrix();

			mesh.vertexArray.bind();
			glUseProgram(mesh.shaderID);

			int mvpMatrixLocation = glGetUniformLocation(mesh.shaderID, "mvpMatrix");
			glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

			if(mesh.usesIndices)
			{
				glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);
			}	
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
			}
		}
	}
}

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

template <class T>
int Tracker<T>::track(T object)
{
	int id = this->size();

	this->push_back(object);

	return id;
}

template <class T>
void Tracker<T>::forget(int id)
{
	this->at(id) = nullptr;
}

// explicit template instantiation
template class Tracker<Mesh *>;

// define MeshTracker and Renderer
Tracker<Mesh *> MeshTracker = Tracker<Mesh *>();
Renderer MeshRenderer = Renderer();
Camera camera = Camera();

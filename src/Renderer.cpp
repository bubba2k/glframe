#include "Renderer.hpp"


Renderer::Renderer() :
	viewHasChanged(true),
	projectionHasChanged(true)
{}

glm::mat4 Renderer::viewMatrix()
{
	if(viewHasChanged)
	{
		m_viewMatrix = glm::lookAt(	glm::vec3(0.0f, 0.0f, 4.0f), 
									glm::vec3(0.0f, 0.0f, 0.0f),
									glm::vec3(0.0f, 1.0f, 0.0f)	);
	
		viewHasChanged = false;
	}

	return m_viewMatrix;
}

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
			glm::mat4 mvpMatrix = projectionMatrix() * viewMatrix() *  mesh.transformationMatrix();

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

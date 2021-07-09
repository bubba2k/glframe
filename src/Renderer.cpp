#include "Renderer.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

float Renderer::aspectRatio;
glm::mat4 Renderer::m_viewMatrix, Renderer::m_projectionMatrix;
bool Renderer::viewHasChanged, Renderer::projectionHasChanged;

bool Renderer::init(float argAspectRatio)
{
	aspectRatio = argAspectRatio;
	projectionHasChanged = true;

	return true;
}

glm::mat4 Renderer::projectionMatrix()
{
	if(projectionHasChanged)
	{
		m_projectionMatrix = glm::perspective(	
					glm::radians(60.0f),	// Vertical FOV
					aspectRatio,			// Aspect Ratio
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
			glm::mat4 mvpMatrix = Renderer::projectionMatrix() * 
				Camera::viewMatrix() *  mesh.transformationMatrix();

			mesh.vertexArray.bind();
			glUseProgram(mesh.shaderID);

			int mvpMatrixLocation = glGetUniformLocation(mesh.shaderID, 
														 "mvpMatrix");
			glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

			if(mesh.usesIndices)
			{
				glDrawElements(GL_TRIANGLES, mesh.vertexCount, 
							   GL_UNSIGNED_INT, 0);
			}	
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
			}
		}
	}
}

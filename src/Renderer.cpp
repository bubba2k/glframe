#include <iostream>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Entity.hpp"

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
	for(Entity *entityPtr : Entity::entityTracker)
	{
		entityPtr->meshPtr->vertexArray.bind();
		glUseProgram(entityPtr->shaderID);

		glm::mat4 entityTransformationMatrix = 
			entityPtr->getTransformationMatrix();

		for(EntityInstance *instancePtr : entityPtr->instanceTracker)
		{
			// Create and send MVP Matrix
			glm::mat4 combinedTransformationMatrix = 
				instancePtr->getTransformationMatrix() * 
				entityTransformationMatrix;

			glm::mat4 mvpMatrix = Renderer::projectionMatrix() * 
				Camera::viewMatrix() * combinedTransformationMatrix;

			int mvpMatrixLocation = glGetUniformLocation(entityPtr->shaderID,
														 "mvpMatrix");

			glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

			if(entityPtr->meshPtr->usesIndices)
			{
				glDrawElements(GL_TRIANGLES, entityPtr->meshPtr->vertexCount,
						   GL_UNSIGNED_INT, 0);
			}		
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, entityPtr->meshPtr->vertexCount);
			}	
		}
	}
}

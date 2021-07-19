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
		ShaderProgram::defaultShader.use();

		glm::mat4 entityTransformationMatrix = 
			entityPtr->getTransformationMatrix();

		for(EntityInstance *instancePtr : entityPtr->instanceTracker)
		{
			// Create and send transformationMatrices
			glm::mat4 modelMatrix = 
				instancePtr->getTransformationMatrix() * 
				entityTransformationMatrix;

			int modelMatrixLocation = glGetUniformLocation(
									  ShaderProgram::defaultShader.getID(),
									  "modelMatrix");
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

			int viewMatrixLocation = glGetUniformLocation(
									 ShaderProgram::defaultShader.getID(),
									 "viewMatrix");
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &Camera::viewMatrix()[0][0]);

			int projectionMatrixLocation = glGetUniformLocation(
										   ShaderProgram::defaultShader.getID(),
										   "projectionMatrix");
			glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &Renderer::projectionMatrix()[0][0]);

			int hasTextureLocation = glGetUniformLocation(
									 ShaderProgram::defaultShader.getID(), "hasTexture");
			// bind texture
			if(entityPtr->texturePtr == nullptr)
			{
				glUniform1i(hasTextureLocation, 0);
			}
			else
			{
				glUniform1i(hasTextureLocation, 1);
				entityPtr->texturePtr->bind();
			}

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

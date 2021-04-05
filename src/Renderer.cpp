#include "Renderer.hpp"

void Renderer::renderMesh(Mesh &mesh)
{
	mesh.buildTransformationMatrix();

	// Create and send MVP Matrix
	glm::mat4 mvpMatrix = mesh.transformationMatrix;

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

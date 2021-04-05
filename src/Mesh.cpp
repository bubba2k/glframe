#include "glframe.hpp"

void Mesh::buildTransformationMatrix()
{
	if(transformationHasChanged)
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), locationVector);
		glm::mat4 scalingMatrix = glm::scale(scalingVector);

		glm::quat rotationQuaternion(rotationVector);
		glm::mat4 rotationMatrix = glm::toMat4(rotationQuaternion);

		transformationMatrix = translationMatrix * rotationMatrix * scalingMatrix;

		transformationHasChanged = false;
	}
}

Mesh::Mesh(GLenum argUsage) :

		usage			(argUsage),

		buffPositions	(usage),
		indexBuffer		(usage),

		usesIndices		(false),

		locationVector	(glm::vec3(0.0f)),
		rotationVector	(glm::vec3(0.0f)),
		scalingVector	(glm::vec3(1.0f)),

		transformationHasChanged(true)

{
	vertexArray.bind();
	indexBuffer.bind();
	buffPositions.bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);
		
	vertexArray.unbind();
}

void Mesh::pushPositions(unsigned int count, float * values)
{
	
	buffPositions.setData(count * 3 * sizeof(float), values);
	
	if(!usesIndices)
	{
		vertexCount = count;
	}
}

void Mesh::pushIndices(unsigned int count, unsigned int * values)
{
	indexBuffer.setData(count * sizeof(unsigned int), values);

	usesIndices = true;

	vertexCount = count;
}

void Mesh::setShader(ShaderProgram &argShader)
{
	shaderID = argShader.getID();
}

void Mesh::setPosition(glm::vec3 argPosition)
{
	locationVector = argPosition;
	transformationHasChanged = true;
}
void Mesh::setPosition(float argPosX, float argPosY, float argPosZ)
{
	locationVector = {argPosX, argPosY, argPosZ};
	transformationHasChanged = true;
}

void Mesh::setRotation(glm::vec3 argRotation)
{	
	rotationVector = argRotation;
	transformationHasChanged = true;
}
void Mesh::setRotation(float argRotX, float argRotY, float argRotZ)
{
	rotationVector = {argRotX, argRotY, argRotZ};
	transformationHasChanged = true;
}

void Mesh::setScale(glm::vec3 argScale)
{
	scalingVector = argScale;
	transformationHasChanged = true;
}
void Mesh::setScale(float argScaleX, float argScaleY, float argScaleZ)
{
	scalingVector = {argScaleX, argScaleY, argScaleZ};
	transformationHasChanged = true;
}
void Mesh::setScale(float argUniformScale)
{
	scalingVector = {argUniformScale, argUniformScale, argUniformScale};
	transformationHasChanged = true;
}

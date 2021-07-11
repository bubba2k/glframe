#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Mesh.hpp"
#include <algorithm>

Tracker<Mesh> Mesh::meshTracker;

Mesh::Mesh(GLenum argUsage) :

		usage			(argUsage),

		buffPositions	(usage),
		indexBuffer		(usage),

		usesIndices		(false)
{
	ID = meshTracker.track(this);

	vertexArray.bind();
	indexBuffer.bind();
	buffPositions.bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);
		
	vertexArray.unbind();
}

Mesh::~Mesh()
{
	meshTracker.forget(this->ID);
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

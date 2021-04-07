#ifndef MESH_HPP
#define MESH_HPP

#include "ShaderProgram.hpp"
#include "Buffers.hpp"
#include "Tracker.hpp"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Mesh
{
	friend class Renderer;

	GLenum usage;

	VertexArray vertexArray;
	VertexBuffer buffPositions;
	IndexBuffer indexBuffer;

	unsigned int vertexCount;

	bool usesIndices;

	unsigned int shaderID;

	glm::vec3 locationVector,
			  rotationVector, // Euler angles
			  scalingVector;

	bool transformationHasChanged;

	glm::mat4 m_transformationMatrix;

	int ID;

	glm::mat4 transformationMatrix();

public:
	Mesh(GLenum usage = GL_STATIC_DRAW);
	~Mesh();

	void pushPositions(unsigned int count, float * values);
	void pushIndices(unsigned int count, unsigned int * values);

	void setShader(ShaderProgram &argShader);

	void setPosition(glm::vec3 argPosition);
	void setPosition(float argX, float argY, float argZ);

	void setRotation(glm::vec3 argRotation);
	void setRotation(float argX, float argY, float argZ);

	void setScale(glm::vec3 argScale);
	void setScale(float argX, float argY, float argZ);
	void setScale(float argUniformScale);
};

extern Tracker<Mesh *> MeshTracker;

#endif

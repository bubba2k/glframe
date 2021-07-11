#ifndef MESH_HPP
#define MESH_HPP

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

#include "ShaderProgram.hpp"
#include "Buffers.hpp"
#include "Tracker.hpp"

class Mesh
{
	friend class Renderer;

	GLenum usage;

	VertexArray vertexArray;
	VertexBuffer buffPositions;
	IndexBuffer indexBuffer;

	unsigned int vertexCount;
	bool usesIndices;

	int ID;

	// keep track of all Meshes
	static Tracker<Mesh> meshTracker;

public:
	Mesh(GLenum usage = GL_STATIC_DRAW);
	~Mesh();

	void pushPositions(unsigned int count, float * values);
	void pushIndices(unsigned int count, unsigned int * values);

	inline int getID() { return this->ID; }
};

#endif

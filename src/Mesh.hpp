#ifndef MESH_HPP
#define MESH_HPP

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

#include "ShaderProgram.hpp"
#include "Buffers.hpp"
#include "Tracker.hpp"

enum MeshShade
{
	SMOOTH,
	FLAT
};

class Mesh
{
	friend class Renderer;

	GLenum usage;

	VertexArray vertexArray;
	VertexBuffer buffPositions;
	VertexBuffer buffNormals;
	VertexBuffer buffTextureCoord;
	IndexBuffer indexBuffer;

	unsigned int vertexCount;
	bool usesIndices;
	bool _hasTextureCoords;

	int ID;

	// keep track of all Meshes
	static Tracker<Mesh> meshTracker;

	void _constructor_setup();

public:
	Mesh(GLenum usage = GL_STATIC_DRAW);
	Mesh(const std::string&, MeshShade shade = MeshShade::SMOOTH, GLenum usage = GL_STATIC_DRAW);
	~Mesh();

	// bla bla rule of three
	Mesh operator=(const Mesh&) = delete;
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&);

	void pushPositions(unsigned int count, float * values);
	void pushIndices(unsigned int count, unsigned int * values);
	void pushNormals(unsigned int count, float * values);
	void pushTextureCoord(unsigned int count, float * values);

	inline int  getID() const { return this->ID; }
	inline bool hasTextureCoords() const { return _hasTextureCoords; };
	inline int  getNumVertices() const { return vertexCount; };
};

#endif

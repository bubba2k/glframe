#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include <algorithm>

Tracker<Mesh> Mesh::meshTracker;

Mesh::Mesh(GLenum argUsage) :

		usage			(argUsage),

		buffPositions	(usage),
		buffNormals     (usage),
		indexBuffer		(usage),

		usesIndices		(false)
{
	ID = meshTracker.track(this);

	vertexArray.bind();
	indexBuffer.bind();

	buffPositions.bind();
	// vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);
	buffPositions.unbind();

	buffNormals.bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(1);
	buffNormals.unbind();

	vertexArray.unbind();
}

Mesh::~Mesh()
{
	meshTracker.forget(this->ID);
}

Mesh::Mesh(Mesh&& that) : vertexArray(std::move(that.vertexArray)),
						  buffNormals(std::move(that.buffNormals)),
						  buffPositions(std::move(that.buffPositions)),
						  indexBuffer(std::move(that.indexBuffer))
{
	usage = that.usage;
	vertexCount = that.vertexCount;
	usesIndices = that.usesIndices;

	ID = that.ID;
	that.ID = -1;
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

Mesh importMesh(const std::string& filePath)
{
    using namespace Assimp;

    Mesh mesh;
    Importer importer;

	const aiScene *scene = importer.ReadFile(filePath, 
			aiProcess_Triangulate | aiProcess_OptimizeGraph |
			aiProcess_OptimizeMeshes);

	std::vector<aiVector3D> vertices, normals;
	for(unsigned i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh * sMesh = scene->mMeshes[i];

		for(unsigned j = 0; j < sMesh->mNumVertices; j++)
			vertices.push_back(sMesh->mVertices[j]);
	}

	mesh.pushPositions(vertices.size() * 3, (float *) &vertices[0]);

	// TODO: hope the move semantics work
	return std::move(mesh);
}

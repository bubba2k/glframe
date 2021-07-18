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
		buffTextureCoord(usage),
		indexBuffer		(usage),

		usesIndices		(false),
		_hasTextureCoords(false)
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

	buffTextureCoord.bind();
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(2);
	buffTextureCoord.unbind();

	vertexArray.unbind();
}

Mesh::~Mesh()
{
	meshTracker.forget(this->ID);
}

Mesh::Mesh(Mesh&& that) : vertexArray(std::move(that.vertexArray)),
						  buffPositions(std::move(that.buffPositions)),
						  buffNormals(std::move(that.buffNormals)),
						  buffTextureCoord(std::move(that.buffTextureCoord)),
						  indexBuffer(std::move(that.indexBuffer))
{
	usage = that.usage;
	vertexCount = that.vertexCount;
	usesIndices = that.usesIndices;
	_hasTextureCoords = that._hasTextureCoords;

	ID = that.ID;
	that.ID = -1;
}

void Mesh::pushPositions(unsigned int count, float * values)
{
	buffPositions.setData(count * 3 * sizeof(float), values);
	
	vertexCount = count;
}

void Mesh::pushNormals(unsigned int count, float * values)
{
	buffNormals.setData(count * 3 * sizeof(float), values);
}

void Mesh::pushTextureCoord(unsigned int count, float * values)
{
	buffTextureCoord.setData(count * 2 * sizeof(float), values);
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
			aiProcess_OptimizeMeshes | aiProcess_GenNormals);

	std::vector<aiVector3D> vertices, normals;

	aiMesh * sMesh = scene->mMeshes[0];

	for(unsigned j = 0; j < sMesh->mNumVertices; j++)
	{
		vertices.push_back(sMesh->mVertices[j]);
		normals.push_back(sMesh->mNormals[j]);
	}

	mesh.pushPositions(vertices.size(), (float *) &vertices[0]);
	mesh.pushNormals(normals.size(), (float *) &normals[0]);

	// TODO: hope the move semantics work
	return std::move(mesh);
}

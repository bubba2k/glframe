#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <array>

#include "Mesh.hpp"
#include <algorithm>

Tracker<Mesh> Mesh::meshTracker;

void Mesh::_constructor_setup()
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

Mesh::Mesh(GLenum argUsage) :
		usage			(argUsage),

		buffPositions	(usage),
		buffNormals     (usage),
		buffTextureCoord(usage),
		indexBuffer		(usage),

		usesIndices		(false),
		_hasTextureCoords(false)
{
	_constructor_setup();
}

Mesh::Mesh(const std::string& filePath, MeshShade shade, GLenum argUsage) :
		usage			(argUsage),

		buffPositions	(usage),
		buffNormals     (usage),
		buffTextureCoord(usage),
		indexBuffer		(usage),

		usesIndices		(false),
		_hasTextureCoords(false)
{
	_constructor_setup();

    using namespace Assimp;

    Importer importer;

	// Make the importer remove the original normals, to recompute them below
	importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
								aiComponent_NORMALS);

	// Flat or smooth normal generation
	int normalFlag = (shade == MeshShade::SMOOTH) ? aiProcess_GenSmoothNormals
												  : aiProcess_GenNormals;

	const aiScene *scene = importer.ReadFile(filePath, 
			aiProcess_Triangulate | aiProcess_OptimizeGraph |
			aiProcess_OptimizeMeshes | aiProcess_RemoveComponent |
			normalFlag);

	std::vector<aiVector3D> vertices, normals;
	std::vector<std::array<float, 2>> texCoords;

	aiMesh * sMesh = scene->mMeshes[0];

	for(unsigned j = 0; j < sMesh->mNumVertices; j++)
	{
		vertices.push_back(sMesh->mVertices[j]);
		normals.push_back(sMesh->mNormals[j]);
	}

	if(sMesh->HasTextureCoords(0) && sMesh->mNumUVComponents[0] > 1)
	{
		for(unsigned j = 0; j < sMesh->mNumVertices; j++)
		{
			texCoords.push_back({sMesh->mTextureCoords[0][j][0],
								 sMesh->mTextureCoords[0][j][1]});
		}
		pushTextureCoord(texCoords.size(), (float *) &texCoords[0]);
	}

	pushPositions(vertices.size(), (float *) &vertices[0]);
	pushNormals(normals.size(), (float *) &normals[0]);
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
	_hasTextureCoords = true;
}

void Mesh::pushIndices(unsigned int count, unsigned int * values)
{
	indexBuffer.setData(count * sizeof(unsigned int), values);

	usesIndices = true;

	vertexCount = count;
}

#ifndef GLFRAME_HPP
#define GLFRAME_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>

#define DISPLAY_DEBUG_MODE 0x1

float getTime();

class Display
{
	SDL_Window* window;
	SDL_GLContext gl_context;
	bool closed;

	public:
	Display(std::string title, int width, int height, int flags = 0);
	~Display();

	void update();
	void clear();
	void setClearColor(float r, float g, float b, float a);

	bool isClosed();
};

class ShaderProgram
{
	std::vector<unsigned int> shaderIDs;
	unsigned int programID;
	unsigned n_Shaders;
	bool valid;

	public:
	ShaderProgram(std::vector<std::string> vecFilenames, std::vector<unsigned int> vecTypes);
	~ShaderProgram();

	unsigned int getID();
	void use();
	bool isValid();
};

class VertexArray
{
	unsigned int id;

	public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;
};

class VertexBuffer
{
	unsigned int id;
	GLenum usage;
	bool dataIsSet;

	void * last_data;
	unsigned int last_size;

	public:
	VertexBuffer(GLenum argUsage, unsigned int size = 0, void * data = nullptr);
	~VertexBuffer();
	
	void bind();
	void unbind();

	void setData(unsigned int size, void * data);
	void refresh();
};

class IndexBuffer
{
	unsigned int id;
	GLenum usage;
	bool dataIsSet;

	void * last_data;
	unsigned int last_size;

	public:
	IndexBuffer(GLenum argUsage, unsigned int size = 0, void * data = nullptr);
	~IndexBuffer();
	
	void bind();
	void unbind();

	void setData(unsigned int size, void * data);
	void refresh();
};

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

	glm::mat4 transformationMatrix;

	unsigned int ID;

	void buildTransformationMatrix();

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

#endif

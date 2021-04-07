#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#include <GL/glew.h>

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

#endif

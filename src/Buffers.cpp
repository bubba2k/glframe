#include "Buffers.hpp"

/* VERTEX ARRAY */

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

VertexArray::VertexArray(VertexArray&& that)
{
	id = that.id;
	that.id = -1;
}

void VertexArray::bind() const
{
	glBindVertexArray(id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

/* VERTEX BUFFER */

VertexBuffer::VertexBuffer(GLenum argUsage, unsigned int size, void * data) :
	usage(argUsage)
{
		glGenBuffers(1, &id);

		if(size != 0 && data != nullptr)
		{
			setData(size, data);
		}
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}

VertexBuffer::VertexBuffer(VertexBuffer&& that)
{
	id = that.id;
	usage = that.usage;
	dataIsSet = that.dataIsSet;

	last_data = that.last_data;
	last_size = that.last_size;

	that.id = -1;
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(unsigned int size, void * data)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	last_data = data;
	last_size = size;

	dataIsSet = true;
}

void VertexBuffer::refresh()
{
	if(dataIsSet == true)
	{
		setData(last_size, last_data);
	}
}

/* INDEX BUFFER */

IndexBuffer::IndexBuffer(GLenum argUsage, unsigned int size, void * data) :
	usage(argUsage)
{
		glGenBuffers(1, &id);

		if(size != 0 && data != nullptr)
		{
			setData(size, data);
		}
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

IndexBuffer::IndexBuffer(IndexBuffer&& that)
{
	id = that.id;
	usage = that.usage;
	dataIsSet = that.dataIsSet;
	last_data = that.last_data;
	last_size = that.last_size;

	that.id = -1;
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(unsigned int size, void * data)
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

	last_data = data;
	last_size = size;

	dataIsSet = true;
}

void IndexBuffer::refresh()
{
	if(dataIsSet == true)
	{
		setData(last_size, last_data);
	}
}

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>
#include <GL/glew.h>

class Texture
{
	unsigned id;

public:
	Texture(const std::string &, GLenum filter = GL_LINEAR);
	Texture() = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&);
	~Texture();

	void bind();
	void unbind();
};

#endif

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>

class Texture
{
	unsigned id;

public:
	Texture() = delete;
	Texture(std::string);
	Texture& operator=(const Texture&) = delete;
	Texture(const Texture&) = delete;
	Texture(Texture&&);
	~Texture();

	void bind();
	void unbind();
};

#endif

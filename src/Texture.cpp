#include <GL/glew.h>
#include <iostream>
#include "Texture.hpp"
#include "../external/stb_image/stb_image.h"

#include <string>

Texture::Texture(const std::string &pathToTexture, GLenum filter)
{
	glGenTextures(1, &id);
	bind();
	// set wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	// load/generate texture
	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char *image_data = stbi_load(pathToTexture.c_str(),
									&width, &height, &nChannels, 4);

	if(image_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
					 GL_UNSIGNED_BYTE, image_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture '" << pathToTexture
				  << "'" << std::endl;
	}

	stbi_image_free(image_data);

	unbind();
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture&& that)
{
	id = that.id;
	// TODO: this might cause bugs, perhaps use 0 isntead?
	//       check same for buffer objects
	that.id = -1;
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

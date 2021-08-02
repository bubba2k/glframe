#ifndef LIGHTSOURCE_HPP_
#define LIGHTSOURCE_HPP_

#include <glm/vec3.hpp>

class LightSource
{
	friend class Renderer;

	static glm::vec3 position, color;
	LightSource() = delete;

	public:
	static void setColor(float, float, float);
	static void setPosition(float, float, float);
};

#endif

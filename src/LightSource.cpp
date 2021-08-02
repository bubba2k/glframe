#include "LightSource.hpp"
#include <glm/detail/qualifier.hpp>

glm::vec3 LightSource::position = glm::vec3{-1.0, 6.0, -1.0};
glm::vec3 LightSource::color = glm::vec3{1.0, 0.95, 0.98};

void LightSource::setPosition(float x, float y, float z)
{
	position = glm::vec3{x, y, z};
}

void LightSource::setColor(float r, float g, float b)
{
	color    = glm::vec3{r, g, b};
}

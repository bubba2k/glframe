#include "libs/Camera.hpp"
#include "libs/GLframe.hpp"

#include <iostream>

int main()
{
	Display display("Window", 1400, 800, 0);

	ShaderProgram shader({"vert.shader", "frag.shader"}, {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER});

	Texture wallTexture("assets/walltexture.jpg");

	Mesh meshIcosphere(importMesh("assets/cubething.dae"));
	Mesh meshTeapot(importMesh("assets/suzanne.obj"));

	Entity entityTeapod;
	entityTeapod.setMesh(meshTeapot);
	entityTeapod.setShader(shader);
	entityTeapod.setTexture(wallTexture);
	auto teapotInstance = entityTeapod.createInstance();

	Entity entityIcosphere;
	entityIcosphere.setMesh(meshIcosphere);
	entityIcosphere.setShader(shader);
	entityIcosphere.setScale(0.65);
	auto icoInstance = entityIcosphere.createInstance();

	std::cout << "Total entity instances: " << numTotalEntityInstances() << 
		std::endl;

	Camera::setPosition(0, 0, 2.5);

	teapotInstance.setPosition(-1.5, 0, -1);
	icoInstance.setPosition(1.5, 0, -1);

	while(!display.isClosed())
	{
		teapotInstance.setRotation(getTime() * 2,
								   getTime() * 3.5,
								   -getTime() * 3.9);

		icoInstance.setRotation(-getTime() * 2.0,
								-getTime() * 3.9,
								getTime() * 2.1);

		display.update();
	}
}

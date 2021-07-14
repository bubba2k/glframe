#include "libs/GLframe.hpp"

#include <iostream>

int main()
{
	Display display("Window", 1400, 800, DISPLAY_DEBUG_MODE);

	ShaderProgram shader({"vert.shader", "frag.shader"}, {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER});

	Mesh meshPyramid;
	Mesh meshTeapot(importMesh("assets/teapot.obj"));

	float vertices[] = { 
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		 0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,	2, 3, 0,	// Bottom

		4, 0, 1,	4, 1, 2,
		4, 2, 3,	4, 3, 0
	};

	meshPyramid.pushPositions(5, vertices);
	meshPyramid.pushIndices(18, indices);

	Entity entityPyramid;
	entityPyramid.setMesh(meshPyramid);
	entityPyramid.setShader(shader);

	Entity entityTeapod;
	entityTeapod.setMesh(meshTeapot);
	entityTeapod.setShader(shader);

	auto teapotInstance = entityTeapod.createInstance();

	std::cout << "Total entity instances: " << numTotalEntityInstances() << 
		std::endl;

	while(!display.isClosed())
	{
		Camera::setPosition(sin(getTime() * 0.15) * 12.0, 
							sin(getTime() * 0.25) * 3.0, 
							cos(getTime() * 0.2) * 10.0);

		display.update();
	}
}

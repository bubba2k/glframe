#include "libs/GLframe.hpp"

#include <iostream>

int main()
{
	Display display("Window", 1400, 800);

	ShaderProgram shader({"vert.shader", "frag.shader"}, {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER});

	Mesh meshPyramid;

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

	entityPyramid.setScale(0.2);

	int dimension = 10;
	std::vector<EntityInstance> pyramids;
	for(int x = -5; x < dimension; x++)
	{
		for(int y = -5; y < dimension; y++)
		{
			for(int z = -5; z < dimension; z++)
			{
				auto instance = entityPyramid.createInstance();
				instance.setPosition(x, y, z);

				pyramids.push_back(instance);
			}
		}
	}

	std::cout << "Total entity instances: " << numTotalEntityInstances() << 
		std::endl;

	while(!display.isClosed())
	{

		for(auto& pyramid : pyramids)
			pyramid.setRotation(getTime() * ( (float) pyramid.getID() / 100.0), 
								getTime() * ( (float) pyramid.getID() / 75.0), 0);

		Camera::setPosition(sin(getTime() * 0.15) * 12.0, sin(getTime() * 0.25) * 3.0, cos(getTime() * 0.2) * 10.0);

		display.update();
		std::cout << getElapsedTime() << "\n";
	}
}

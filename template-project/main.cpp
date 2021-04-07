#include "libs/GLframe.hpp"

int main()
{
	Display display("Window", 800, 600);

	ShaderProgram shader({"vert.shader", "frag.shader"}, {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER});

	Mesh mesh;
	mesh.setShader(shader);

	Mesh mesh2;
	mesh2.setShader(shader);


	Mesh mesh3;
	mesh3.setShader(shader);

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

	mesh.pushPositions(5, vertices);
	mesh.pushIndices(18, indices);

	mesh2.pushPositions(5, vertices);
	mesh2.pushIndices(18, indices);


	mesh3.pushPositions(5, vertices);
	mesh3.pushIndices(18, indices);

	mesh.setScale(1.3f);
	mesh2.setPosition(3, 0, 0);
	mesh2.setScale(0.9f);

	mesh3.setScale(0.9f, 0.4f, 0.2f);

	while(!display.isClosed())
	{
		mesh2.setRotation(10.0f * getTime(), 5.0f * getTime(), getTime());
		mesh.setRotation (0.5f * getTime(), 0.0f, 0.6f * getTime());

		mesh3.setPosition(0.0f, cos(getTime()*2.0f) * 3.0f, sin(getTime()*2.0f) * 2.0f);
		mesh3.setRotation(getTime()*180.0f, 0, 0);

		camera.setPosition(6.0f * cos(getTime()*0.1), 0, 6.0f * sin(getTime()*0.1));


		display.update();
	}
}

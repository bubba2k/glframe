#include "libs/GLframe.hpp"

int main()
{
	Display display("Window", 800, 600);

	ShaderProgram shader({"vert.shader", "frag.shader"}, {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER});

	Mesh mesh;
	mesh.setShader(shader);

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

	mesh.setScale(1.3f);

	while(!display.isClosed())
	{
		mesh.setRotation(0.0f, getTime() * 6.0f, getTime());

		display.update();
	}
}

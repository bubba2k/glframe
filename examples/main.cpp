#include "../src/GLframe.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	int flags = 0;
	if(argc > 1)
		flags |= DISPLAY_DEBUG_MODE;

	Display display("Object Viewer", 1024, 720, flags);

	Mesh catMesh("assets/cat/concrete_cat_statue_2k.obj", MeshShade::SMOOTH);
	std::cout << "Donut has this many vertices: " << 
				 catMesh.getNumVertices() << std::endl;

	Texture catTexture("assets/cat/textures/concrete_cat_statue_diff_2k.jpg", GL_LINEAR);

	Entity catEntity;
	catEntity.setMesh(catMesh); 
	catEntity.setTexture(catTexture);

	auto catInstance = catEntity.createInstance();

	Camera::setPosition(0, 0, 0.4);

	catInstance.setPosition(-0.02, -0.13, 0);

	while(!display.isClosed())
	{
		catInstance.setRotation(0.0, getTime() * 1.8f, 0.0);

		display.update();
	}
}

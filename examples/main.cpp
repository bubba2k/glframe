#include "../src/GLframe.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	int flags = 0;
	if(argc > 1)
		flags |= DISPLAY_DEBUG_MODE;

	Display display("Window", 1400, 800, flags);

	Mesh tableMesh("assets/table/table.dae");
	Mesh donutMesh("assets/donut/donut.obj", MeshShade::SMOOTH);
	std::cout << "Donut has this many vertices: " << 
				 donutMesh.getNumVertices() << std::endl;

	Texture tableTex("assets/table/wood128.png", GL_NEAREST),
			donutTex("assets/donut/donut_texture.png", GL_NEAREST);

	Entity tableEnt, donutEnt;
	tableEnt.setMesh(tableMesh); tableEnt.setTexture(tableTex);
	donutEnt.setMesh(donutMesh); donutEnt.setTexture(donutTex);

	auto donut = donutEnt.createInstance(), table = tableEnt.createInstance();
	table.setVisible(false);

	Camera::setPosition(0, 0, 0.4);

	donut.setPosition(0, 0, 0);

	while(!display.isClosed())
	{
		donut.setRotation(getTime() * 7.0, getTime() * 0.4, getTime() * 9.0);

		display.update();
	}
}

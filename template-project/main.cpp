#include "libs/GLframe.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	int flags = 0;
	if(argc > 1)
		flags |= DISPLAY_DEBUG_MODE;

	Display display("Window", 1400, 800, flags);

	Mesh botMesh("assets/framebot.dae");

	Texture wallTexture("assets/framebottex.png");
	Texture framebotTexture("assets/framebottex.png");

	Mesh triangleMesh;
	float pos[] = {0.0, 0.0, 0.0,
				   1.0, 1.0, 0,
				   0.0, 1.0, 0};
	float uv[]  = {0.0, 0.0,
				   1.0, 1.0,
				   0.0, 1.0};
	triangleMesh.pushPositions(3, pos);
	triangleMesh.pushTextureCoord(3, uv);

	Entity triangle;
	triangle.setMesh(triangleMesh);
	triangle.setTexture(framebotTexture);

	Entity botEnt;
	botEnt.setMesh(botMesh);
	botEnt.setRotation(0, 90, 0);
	botEnt.setTexture(wallTexture);
	
	auto botInstance = botEnt.createInstance();
	botInstance.setScale(0.5);
	// auto triInstance = triangle.createInstance();

	Camera::setPosition(0, 0, 2.5);

	while(!display.isClosed())
	{
		botInstance.setRotation(getTime() * 7.0, getTime() * 5.0, 0);

		display.update();
	}
}

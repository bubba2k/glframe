#include "Util.hpp"

#include <SDL2/SDL.h>

#include "Entity.hpp"

float getTime()
{
	return (float) SDL_GetTicks() / 1000.0f;
}

int getElapsedTime()
{
	static int last;

	int time = SDL_GetTicks();
	int diff = time - last;
	last = time;

	return diff;
}

int numTotalEntityInstances()
{
	int n = 0;
	for(auto entity : Entity::entityTracker)
	{
		n += entity->getNumInstances();
	}

	return n;
}

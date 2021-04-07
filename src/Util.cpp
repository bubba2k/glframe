#include "Util.hpp"

#include <SDL2/SDL.h>

float getTime()
{
	return (float) SDL_GetTicks() / 1000.0f;
}

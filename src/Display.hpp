#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SDL2/SDL.h>
#include <string>

#define DISPLAY_DEBUG_MODE 0x1

class Display
{
	SDL_Window* window;
	SDL_GLContext gl_context;
	bool closed;

	float _aspectRatio;

	public:
	Display(std::string title, int width, int height, int flags = 0);
	~Display();

	void update();
	void clear();
	void setClearColor(float r, float g, float b, float a);

	bool isClosed();
};

extern Display display;

#endif

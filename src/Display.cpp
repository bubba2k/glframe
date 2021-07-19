#include <GL/glew.h>

#include "Display.hpp"
#include "Renderer.hpp"
#include "ShaderProgram.hpp"

static void DebugMessageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data);


Display::Display(std::string title, int width, int height, int flags)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Set the sie of the color data
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	// Enable double buffer mode
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Enable Multisampling
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// request version and core profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
						SDL_GL_CONTEXT_PROFILE_CORE);

	if(flags & DISPLAY_DEBUG_MODE)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	SDL_GL_SetSwapInterval(0);

	window =  SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 
							   SDL_WINDOWPOS_CENTERED, width, height, 
							   SDL_WINDOW_OPENGL);

	gl_context = SDL_GL_CreateContext(window);

	glewInit();

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if(flags & DISPLAY_DEBUG_MODE)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(DebugMessageCallback, NULL);
	}

	// Init the renderer
	float aspectRatio = (float) width / (float) height;
	Renderer::init(aspectRatio);
	// Init default Shader
	ShaderProgram::init();

	closed = false;
}

Display::~Display()
{
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::update()
{
	clear();

	Renderer::renderScene();

	SDL_GL_SwapWindow(window);

	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			closed = true;
		else if(e.key.keysym.sym == SDLK_ESCAPE)
			closed = true;
	}

}

void Display::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::setClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
{
	glClearColor(r, g, b, a);
}

bool Display::isClosed()
{
	return closed;
}



static void DebugMessageCallback(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar *msg, const void *data)
{
	std::string _source;
	std::string _type;
	std::string _severity;

	// suppress unused warnings
	data = data;
	length = length;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

        case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

        case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

        default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

        case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

        case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

        case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

        default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

        case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

        case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

        default:
        _severity = "UNKNOWN";
        break;
    }

    printf("%d: %s of %s severity, raised from %s: %s\n",
            id, _type.c_str(), _severity.c_str(), _source.c_str(), msg);
}

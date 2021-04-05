#ifndef GLHELPERS_HPP
#define GLHELPERS_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>

static float getTime(void)
{
	float time = (float) SDL_GetTicks() / 1000.0f;
	return time;
};

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

#define DISPLAY_DEBUG_MODE 0x1

class Display
{
	// not intended for handling input besides quit event

	SDL_Window* window;
	SDL_GLContext gl_context;
	bool closed;

	public:
	Display(std::string title, int width, int height, int flags = 0)
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
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		if(flags & DISPLAY_DEBUG_MODE)
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

		SDL_GL_SetSwapInterval(0);

		window =  SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

		gl_context = SDL_GL_CreateContext(window);

		glewInit();

		glEnable(GL_MULTISAMPLE);

		if(flags & DISPLAY_DEBUG_MODE)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(DebugMessageCallback, NULL);
		}

		closed = false;
	}

	~Display()
	{
		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void update()
	{
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

	void clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void setClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
	{
		glClearColor(r, g, b, a);
	}

	bool isClosed()
	{
		return closed;
	}
};

class ShaderProgram
{
	std::vector<GLuint> shaderIDs;
	GLuint programID;

	unsigned n_Shaders;

	bool valid;

	public:
	ShaderProgram(std::vector<std::string> vecFilenames, std::vector<GLuint> vecTypes)
	{
		programID = 0;

		if(vecTypes.size() != vecFilenames.size())
		{
			std::cerr << "ERROR: Non-matching count of arguments to constructor of ShaderProgram" << std::endl;

			valid = false;
			return;
		}

		n_Shaders = vecFilenames.size();

		for(unsigned i = 0; i < n_Shaders; i++)
		{
			std::ifstream infile(vecFilenames.at(i));
			std::stringstream sstream;
			sstream << infile.rdbuf();

			std::string source(sstream.str());

			const char * source_c_str = source.c_str();

			GLuint shaderID = glCreateShader(vecTypes.at(i));

			// Compile
			glShaderSource(shaderID, 1, &source_c_str, NULL);
			glCompileShader(shaderID);

			// Check
			int success;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if(!success)
			{
				char infoLog[512];

				glGetShaderInfoLog(shaderID, 512, NULL, infoLog);

				std::cerr << "ERROR: Failed to compile shader '" << vecFilenames.at(i) << "':\n" <<  infoLog << std::endl;

				valid = false;

				return;
			}

			shaderIDs.push_back(shaderID);
		}

		programID = glCreateProgram();

		for(unsigned i = 0; i < n_Shaders; i++)
		{
			glAttachShader(programID, shaderIDs.at(i));
		}

		glLinkProgram(programID);

		int success;
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if(!success)
		{
			char infoLog[512];

			glGetProgramInfoLog(programID, 512, NULL, infoLog);

			std::cerr << "ERROR: Failed to link shader program from shaders: ";
			for(unsigned int i = 0; i < vecFilenames.size(); i++)
			{
				std::cerr << vecFilenames.at(i) << " | ";
			}
			std::cerr << std::endl << infoLog << std::endl;

			valid = false;

			return;
		}

		for(unsigned int i = 0; i < shaderIDs.size(); i++)
			glDetachShader(programID, shaderIDs.at(i));

		valid = true;
	}

	~ShaderProgram()
	{
		for(unsigned i = 0; i < shaderIDs.size(); i++)
		{
			glDeleteShader(shaderIDs.at(i));
		}

		glDeleteProgram(programID);
	}

	GLuint ID(void)
	{
		return programID;
	}

	void use()
	{
		glUseProgram(programID);
	}

	bool isValid()
	{
		return valid;
	}
};

class VertexArray
{
	unsigned int id;

	public:
	VertexArray()
	{
		glGenVertexArrays(1, &id);
	}

	~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void bind() const
	{
		glBindVertexArray(id);
	}

	void unbind() const
	{
		glBindVertexArray(0);
	}
};

class VertexBuffer
{
	unsigned int id;
	GLenum usage;

	bool dataIsSet;

	void * last_data;
	unsigned int last_size;

	public:
	VertexBuffer(GLenum argUsage, unsigned int size = 0, void * data = nullptr) : usage(argUsage)
	{
		glGenBuffers(1, &id);

		if(size != 0 && data != nullptr)
		{
			setData(size, data);
		}
	}

	~VertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void setData(unsigned int size, void * data)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);

		last_data = data;
		last_size = size;

		dataIsSet = true;
	}

	void refresh()
	{
		if(dataIsSet == true)
		{
			setData(last_size, last_data);
		}
	}
};

class IndexBuffer
{
	unsigned int id;
	GLenum usage;

	bool dataIsSet;

	void * last_data;
	unsigned int last_size;

	public:
	IndexBuffer(GLenum argUsage, unsigned int size = 0, void * data = nullptr) : usage(argUsage)
	{
		glGenBuffers(1, &id);

		if(size != 0 && data != nullptr)
		{
			setData(size, data);
		}
	}

	~IndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void setData(unsigned int size, void * data)
	{
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

		last_data = data;
		last_size = size;

		dataIsSet = true;
	}

	void refresh()
	{
		if(dataIsSet == true)
		{
			setData(last_size, last_data);
		}
	}
};

class Mesh
{
	friend class Renderer;

	GLenum usage;

	VertexArray vertexArray;
	VertexBuffer buffPositions;
	IndexBuffer indexBuffer;

	unsigned int vertexCount;

	bool usesIndices;

	unsigned int shader;


	glm::vec3 location,
			  rotation, // Euler angles
			  scale;

	bool transformationHasChanged;

	glm::mat4 transformationMatrix;

	unsigned int id;

	void buildTransformationMatrix()
	{
		if(transformationHasChanged)
		{
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), location);
			glm::mat4 scalingMatrix = glm::scale(scale);

			glm::quat rotationQuaternion(rotation);
			glm::mat4 rotationMatrix = glm::toMat4(rotationQuaternion);

			transformationMatrix = translationMatrix * rotationMatrix * scalingMatrix;

			transformationHasChanged = false;
		}
	}

	public:
	Mesh() : 

		usage(GL_STATIC_DRAW),

		buffPositions(usage),
		indexBuffer(usage),

		usesIndices(false),

		location(glm::vec3(0.0f)),
		rotation(glm::vec3(0.0f)),
		scale(glm::vec3(1.0f)),

		transformationHasChanged(true)
	{
		vertexArray.bind();
		indexBuffer.bind();
		buffPositions.bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
		glEnableVertexAttribArray(0);
		
		vertexArray.unbind();
	}
	
	void pushPositions(unsigned int count, float * values)
	{
		buffPositions.setData(count * 3 * sizeof(float), values);
		
		if(!usesIndices)
		{
			vertexCount = count;
		}
	}

	void pushIndices(unsigned int count, unsigned int * values)
	{
		indexBuffer.setData(count * sizeof(unsigned int), values);

		usesIndices = true;

		vertexCount = count;
	}

	void setShader(ShaderProgram &argShader)
	{
		shader = argShader.ID();
	}

	void setPosition(glm::vec3 argPosition)
	{
		this->location = argPosition;
		transformationHasChanged = true;
	}
	void setPosition(float argPosX, float argPosY, float argPosZ)
	{
		this->location = {argPosX, argPosY, argPosZ};
		transformationHasChanged = true;
	}

	void setRotation(glm::vec3 argRotation)
	{	
		this->rotation = argRotation;
		transformationHasChanged = true;
	}
	void setRotation(float argRotX, float argRotY, float argRotZ)
	{
		this->rotation = {argRotX, argRotY, argRotZ};
		transformationHasChanged = true;
	}

	void setScale(glm::vec3 argScale)
	{
		this->scale = argScale;
		transformationHasChanged = true;
	}
	void setScale(float argScaleX, float argScaleY, float argScaleZ)
	{
		this->scale = {argScaleX, argScaleY, argScaleZ};
		transformationHasChanged = true;
	}
};

class Scene
{
	friend class Renderer;

	std::vector<Mesh *> vecMeshes;
};

class Renderer
{
	glm::mat4 viewMatrix, projectionMatrix;

	public:
	void renderMesh(Mesh &mesh)
	{
		mesh.buildTransformationMatrix();

		// Create and send MVP Matrix
		glm::mat4 mvpMatrix = mesh.transformationMatrix;

		mesh.vertexArray.bind();
		glUseProgram(mesh.shader);

		int mvpMatrixLocation = glGetUniformLocation(mesh.shader, "mvpMatrix");
		glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

		if(mesh.usesIndices)
		{
			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
		}
	}
};

#endif

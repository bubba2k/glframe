#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "ShaderProgram.hpp"

#include <string>

#include "ShaderProgram.hpp"

const std::string vertSource = R"STR(
#version 450

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 localPosition;
out vec3 localNormal;
out vec2 localTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    vec4 transformedPosition = vec4(aPos.xyz, 1);
    transformedPosition = mvpMatrix * transformedPosition;

    gl_Position = transformedPosition;

    localPosition = aPos;
    localNormal   = aNormal;
    localTexCoord = aTexCoord;
}
)STR";

const std::string fragSource = R"STR(
#version 450

in  vec3 localPosition;
in  vec3 localNormal;
in  vec2 localTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform sampler2D theTexture;
uniform bool hasTexture;

out vec4 FragColor;

void main()
{
	if(hasTexture)
		FragColor = texture(theTexture, localTexCoord);
	else
		FragColor = vec4(localPosition * vec3(0.5, 0.5, 0.5) 
						 + vec3(0.5, 0.5, 0.5), 1);
}
)STR";

ShaderProgram ShaderProgram::defaultShader;

void ShaderProgram::init()
{
	ShaderProgram::defaultShader.fromStrings({vertSource, fragSource});
}

ShaderProgram::ShaderProgram()
{
	programID = 0;
	n_Shaders = 0;
	valid = false;
};

void ShaderProgram::fromStrings(std::vector<std::string> vecSources)
{
	programID = 0;

	if(vecSources.size() != 2)
		std::cerr << "Failed to compile shader: need 1. vert, 2. frag shader"
			      << std::endl;

	n_Shaders = vecSources.size();

	for(unsigned i = 0; i < n_Shaders; i++)
	{
		const char * source_c_str = vecSources[i].c_str();

		GLuint shaderType;
		if(i == 0)
			shaderType = GL_VERTEX_SHADER;
		else
			shaderType = GL_FRAGMENT_SHADER;

		GLuint shaderID = glCreateShader(shaderType);

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

			std::cerr << "ERROR: Failed to compile shader '" << vecSources.at(i) << "':\n" <<  infoLog << std::endl;

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
		for(unsigned int i = 0; i < vecSources.size(); i++)
		{
			std::cerr << vecSources.at(i) << " | ";
		}
		std::cerr << std::endl << infoLog << std::endl;
		valid = false;

		return;
	}

	for(unsigned int i = 0; i < shaderIDs.size(); i++)
		glDetachShader(programID, shaderIDs.at(i));

	valid = true;
}

ShaderProgram::ShaderProgram(std::vector<std::string> vecFilenames, std::vector<GLuint> vecTypes)
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

ShaderProgram::~ShaderProgram()
{
	for(unsigned i = 0; i < shaderIDs.size(); i++)
	{
		glDeleteShader(shaderIDs.at(i));
	}

	glDeleteProgram(programID);
}

unsigned int ShaderProgram::getID(void)
{
	return programID;
}

void ShaderProgram::use()
{
	glUseProgram(programID);
}

bool ShaderProgram::isValid()
{
	return valid;
}

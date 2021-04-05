#include "glframe.hpp"

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

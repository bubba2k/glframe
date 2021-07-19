#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <vector>
#include <string>

class ShaderProgram
{
	std::vector<unsigned int> shaderIDs;
	unsigned int programID;
	unsigned n_Shaders;
	bool valid;

	public:
	ShaderProgram();
	ShaderProgram(std::vector<std::string> vecFilenames, std::vector<unsigned int> vecTypes);
	void fromStrings(std::vector<std::string> vecSources);
	~ShaderProgram();

	static ShaderProgram defaultShader;
	static void init();

	unsigned int getID();
	void use();
	bool isValid();
};


#endif

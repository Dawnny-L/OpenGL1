
#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create vertex shader object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	//Create fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Fragment shader source to the Fragment Shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the vertex Shader into machine code
	glCompileShader(fragmentShader);

	//Create Shader program object and get its reference
ID = glCreateProgram();
	//Attach vertex and fragment shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Wrap-up/Link all the shaders together into the shader program
	glLinkProgram(ID);

	//Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
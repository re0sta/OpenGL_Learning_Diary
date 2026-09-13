#include "Shader.h"
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		if (!vertexFile.is_open()||!fragmentFile.is_open())
			throw std::exception("Fail to open file");

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vertexFile.rdbuf();
		fShaderStream <<fragmentFile.rdbuf();

		vertexString = vShaderStream.str();
		fragmentString = fShaderStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "SHADER");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "SHADER");


		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception&x)
	{
		std::cout << x.what() << std::endl;
	}

}
void Shader::use() {
	glUseProgram(ID);
}
void Shader::checkCompileErrors(unsigned int ID, std::string type) {
	int success;
	char inforLog[512];
	if (type == "PROGRAM") {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, inforLog);
			std::cout << "link error: " << inforLog << std::endl;
		}
	}
	if (type == "SHADER") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, inforLog);
			std::cout << "compile error: " << inforLog << std::endl;
		}
	}
}

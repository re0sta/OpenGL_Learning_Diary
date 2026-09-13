#pragma once
#define GLEW_STATIC	
#include <iostream>
#include<fstream>
#include<sstream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
class Shader
{public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void checkCompileErrors(unsigned int ID, std::string type);
	void use();
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource = nullptr;
	const char* fragmentSource = nullptr;
	unsigned int ID=0;//shader_program ID

};


#include <fstream>
#include <iostream>

#include "Shader.h"



static std::string LoadShader(const std::string& filename);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);


Shader::Shader(const std::string & filename) {
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);	

	for(uint_32 i = 0; i < NUM_SHADER; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR SHADER PROGRAM FAILED LINKING");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "ERROR SHADER PROGRAM FAILED TO VERIFY");
}

void Shader::Bind(){
	glUseProgram(m_program);
}


static GLuint CreateShader(const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "ERROR SHADER CREATION FAILED" << std::endl;

	GLint shaderStringsSize[1];
	const GLchar* shaderStrings[1];
	shaderStrings[0] = text.c_str();
	shaderStringsSize[0] = text.length();

	glShaderSource(shader, 1, shaderStrings, shaderStringsSize);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "SHADER COMPILATION FAILED");

	return shader;
}
static std::string LoadShader(const std::string& filename){
	std::ifstream file;
	file.open((filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader:" << filename << std::endl;
	}
	return output;
}
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage){
	GLint succes = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &succes);
	else
		glGetShaderiv(shader, flag, &succes);
	if(succes == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
	}

}

Shader::~Shader() {
	for (uint_32 i = 0; i < NUM_SHADER; i++) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

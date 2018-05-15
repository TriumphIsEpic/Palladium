#pragma once
#include "Engine.h"

#include <string>
#include <GL/glew.h>

class Shader {
	public:
		Shader(const std::string& filename);
		void Bind();
		virtual ~Shader();
	private:
		static const uint_32 NUM_SHADER = 2;
		GLuint m_program;
		GLuint m_shaders[NUM_SHADER];
};


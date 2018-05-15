#pragma once
#include "Engine.h"

#include <glm\glm.hpp>
#include <GL\glew.h>

struct Vertex {
	glm::vec3 pos;
	Vertex(const glm::vec3& pos) {
		this->pos = pos;
	}
};


class Mesh {
public:
	Mesh(Vertex* verticies, uint_32 numVerticies);
	virtual void Draw();
	virtual ~Mesh();
private:
	enum {
		POSITION_VB,

		NUM_BUFFERS
	};


	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	uint_32 m_drawCount;
};


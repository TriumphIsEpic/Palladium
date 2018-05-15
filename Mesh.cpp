#include "Mesh.h"



Mesh::Mesh(Vertex* verticies, uint_32 numVerticies) {
	m_drawCount = numVerticies;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVerticies * sizeof(verticies[0]), verticies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	glBindVertexArray(0);
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}


Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

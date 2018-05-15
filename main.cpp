#include <iostream>
#include <GL/glew.h>

#include "display.h"
#include "Shader.h"
#include "Mesh.h"

int main(int argc, char** argv) {
	Display display(800, 600, "Engine Core");
	Shader shader("resources/shaders/basicShader");
	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0)),
						 Vertex(glm::vec3(0,0.5,0)),
						 Vertex(glm::vec3(0.5,-0.5,0)) };
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	while(!display.isCLosed) {
		display.Clear(0.1f, 0.2f, 0.1f, 1.0f);
		shader.Bind();
		mesh.Draw();

		display.Update();
	}

	return 0;
}
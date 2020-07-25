#include "Grid.h"

Grid::Grid(int size) {
	type = GL_TRIANGLES;
	vertices = std::vector < glm::vec3>(4 * (size + 1));//n*n squares require 2(n+1) lines

	float offset = (size % 2 == 0) ? size/2 : (size/2) + 0.5f;//offset needed about (0.0) depending on odd/even square grid
	//for (int i = 0; i <= size; ++i) {
	//	vertices[4 * i]		= glm::vec3(i - offset, 0.0f, -offset);
	//	vertices[4 * i + 1] = glm::vec3(i - offset, 0.0f, offset);
	//	vertices[4 * i + 2] = glm::vec3(-offset, 0.0f, i-offset);
	//	vertices[4 * i + 3] = glm::vec3(offset, 0.0f, i - offset);
	//}

	for (int i = 0; i <= size; i++) {
		vertices = {
		glm::vec3(i -(-0.5f), -0.5f, -0.5f),
			glm::vec3(i-(0.5f), -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, i-0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, i-0.5f),
			glm::vec3(-0.5f, -0.5f, i-0.5f),
		};
	}

	colours = std::vector < glm::vec3>(vertices.size());
	for (unsigned int i = 0; i < colours.size(); ++i) {
		colours[i] = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	setupBufferData();
}

Grid::~Grid() {
}

void Grid::draw() {
	glLineWidth(3.0f);
	Drawable::draw();
	glLineWidth(1.0f);
}
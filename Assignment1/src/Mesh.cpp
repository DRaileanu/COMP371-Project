#include "Mesh.h"


Mesh::Mesh() {
	glGenVertexArrays(1, &VAO);
	VBO = CBO = EBO = 0;
	type = GL_TRIANGLES;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &CBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::setupBufferData() {
	glBindVertexArray(VAO);
	//positions
	if (vertices.empty()) { return; }//try removing and see if works with empty mesh
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//colours (if specified)
	if (!colours.empty()) {
		glGenBuffers(1, &CBO);
		glBindBuffer(GL_ARRAY_BUFFER, CBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colours.size(), &colours[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
	//indices (if specified)
	if (!indices.empty()) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}

	glBindVertexArray(0);
}

void Mesh::draw() {
	glBindVertexArray(VAO);
	if (EBO) {
		glDrawElements(type, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(type, 0, vertices.size());
	}

	glBindVertexArray(0);
}


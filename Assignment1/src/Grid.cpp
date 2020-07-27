#include "Grid.h"

Grid::Grid() {
	//vertices.reserve(100*100*2*3);//n*n squares * 2 triangles/square * 3 vertices/triangle

	vertices.push_back(glm::vec3(-50.0, 0.0f, 50.0));
	vertices.push_back(glm::vec3(50.0, 0.0f, -50.0));
	vertices.push_back(glm::vec3(-50.0, 0.0f, -50.0));

	vertices.push_back(glm::vec3(-50.0, 0.0f, 50.0));
	vertices.push_back(glm::vec3(50.0, 0.0f, 50.0));
	vertices.push_back(glm::vec3(50.0, 0.0f, -50.0));


	colours = std::vector < glm::vec3>(vertices.size());
	for (unsigned int i = 0; i < colours.size(); ++i) {
		colours[i] = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	normals = std::vector<glm::vec3>(vertices.size());
	for (unsigned int i = 0; i < normals.size(); ++i) {
		normals[i] = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	texCoords.push_back(glm::vec2(0.0, 0.0f));
	texCoords.push_back(glm::vec2(50.0, 50.0f));
	texCoords.push_back(glm::vec2(0.0, 50.0f));

	texCoords.push_back(glm::vec2(0.0, 0.0f));
	texCoords.push_back(glm::vec2(50.0, 0.0f));
	texCoords.push_back(glm::vec2(50.0, 50.0f));

	setupBufferData();
}

Grid::~Grid() {
}

void Grid::addSquare(float x, float z) {
	vertices.push_back(glm::vec3(x, 0.0, z));
	vertices.push_back(glm::vec3(x+1.0, 0.0, z-1.0));
	vertices.push_back(glm::vec3(x, 0.0, z-1.0));

	vertices.push_back(glm::vec3(x, 0.0, z));
	vertices.push_back(glm::vec3(x + 1.0, 0.0, z));
	vertices.push_back(glm::vec3(x + 1.0, 0.0, z-1.0));

	texCoords.push_back(glm::vec2(0.0, 0.0));
	texCoords.push_back(glm::vec2(1.0, 1.0));
	texCoords.push_back(glm::vec2(0.0, 1.0));

	texCoords.push_back(glm::vec2(0.0, 0.0));
	texCoords.push_back(glm::vec2(1.0, 0.0));
	texCoords.push_back(glm::vec2(1.0, 1.0));
}
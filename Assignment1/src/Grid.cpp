#include "Grid.h"


float f(float x, float y)
{
    // use any curve function you want
    return sin(x * 2.0f * 3.141526f) * sin(y * 2.0f * 3.141526f) * 0.1f;
}

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
    for (int j = 0; j <= size; ++j)
    {
        for (int i = 0; i <= size; ++i)
        {
            float x = (float)i / (float)size;
            float y = (float)j / (float)size;
            float z = 1.0f;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for (int j = 0; j < size; ++j)
    {
        for (int i = 0; i < size; ++i)
        {
            int row1 = j * (size + 1);
            int row2 = (j + 1) * (size + 1);

            // triangle 1
            vertices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i + 1));

            // triangle 2
            vertices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
        }
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
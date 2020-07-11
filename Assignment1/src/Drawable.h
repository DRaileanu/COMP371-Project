#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

//base class for drawable geometry
//can be instantiated on its own, but useless since no way to provide geometry data, use a class that inherits it

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

	//provides basic implementation for drawing geometry
	virtual void draw();

protected:
	//handles setup of data buffers into coresponding array object
	void setupBufferData();

	GLuint VAO;//array object
	GLuint VBO;//vertex buffer
	GLuint CBO;//color buffer
	GLuint EBO;//element(index) buffer
	GLuint type;//type of primitive

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colours;
	std::vector<unsigned int> indices;
};


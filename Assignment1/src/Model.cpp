#include "Model.h"

Model::Model(char c) {
	cube = new Cube;
	switch (c) {
	case 'N': {createN(); }
	break;
	case '1': {create1(); }
	break;
	case 'H': {createH(); }
	break;
	case '5': {create5(); }
	break;
	case '2': {create2(); }
	break;
	case 'D': {createD(); }
	break;
	case '3': {create3(); }
	break;
	}
}

Model::~Model() {
	delete cube;
}

void Model::createN() {
	DrawNode* node;
	GLuint texture = loadTexture("res/container.jpg");

	Material* material = new Material{glm::vec3(0.25, 0.25, 0.25), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.75, 0.75f, 0.75f), 32.0 };
	node = new DrawNode(cube);
	node->setTexture(texture);
	node->setMaterial(material);
	node->scale(glm::vec3(2.0f, 2.0, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, -1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	addChild(node);

	node = new DrawNode(cube);
	node->setTexture(texture);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->setTexture(texture);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(-1.5f, 2.5f, 0.0f));
	addChild(node);
}

void Model::create1() {
	DrawNode* node;

	GLuint texture = loadTexture("res/container.jpg");

	node = new DrawNode(cube);
	node->setTexture(texture);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->setTexture(texture);
	node->scale(glm::vec3(1.25f, 1.0f, 1.0f));
	node->translate(glm::vec3(-1.125, 4.0f, 0.0f));
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	addChild(node);
}

void Model::createH() {
	DrawNode* node;
	node = new DrawNode(cube);
	node->scale(glm::vec3(2.0f, 1.0, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(-1.5f, 2.5f, 0.0f));
	addChild(node);
}
void Model::create5() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 0.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 4.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->translate(glm::vec3(-1.5f, 3.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->translate(glm::vec3(1.5f, 1.5f, 0.0f));
	addChild(node);

}

void Model::create2() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(2.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 4.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 4.25f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(3.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->scale(glm::vec3(1.0f, 2.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.5f, 0.5, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 0.75f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 4.25f, 0.0f));
	addChild(node);
}

void Model::createD() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, -1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.5f, 3.75f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(-1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, 1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.5f, 1.25f, 0.0f));
	addChild(node);
}

void Model::create3() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 0.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 2.5f, 0.0f));
	addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 4.5f, 0.0f));
	addChild(node);
}


void Model::setColours(glm::vec3 newColour) {
	cube->setColours(newColour);
}
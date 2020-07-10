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

}

void Model::createN() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	node->scale(glm::vec3(2.0f, 2.0, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	node->shear(glm::mat4(
		glm::vec4(1.0f, -1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(-1.5f, 2.5f, 0.0f));
	addChild(node);
	
}

void Model::create1() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.25f, 1.0f, 1.0f));
	node->translate(glm::vec3(-1.125, 4.0f, 0.0f));
	node->shear(glm::mat4(
		glm::vec4(1.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	addChild(node);
}

void Model::createH() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	node->scale(glm::vec3(2.0f, 1.0, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(-1.5f, 2.5f, 0.0f));
	addChild(node);
}
void Model::create5() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 0.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 4.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->translate(glm::vec3(-1.5f, 3.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->translate(glm::vec3(1.5f, 1.5f, 0.0f));
	addChild(node);

}


void Model::create2() {
	create5();
	this->scale(glm::vec3(-1.0f, 1.0f, 1.0f));
}

void Model::createD() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	node->shear(glm::mat4(
		glm::vec4(1.0f, -1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.5f, 3.75f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 2.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(-1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->shear(glm::mat4(
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
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 5.0f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 0.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 2.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 4.5f, 0.0f));
	addChild(node);
}
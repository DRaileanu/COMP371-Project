#include "Model.h"


Model::Model(char c, glm::vec3 colour) {
	cube = new Cube(colour);
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

	//new methods added for Quiz1
	case 'R': {createR(); }
			break;
	case 'A': {createA(); }
			break;
	case 'I': {createI(); }
			break;
	case 'L': {createL(); }
			break;
	case 'E': {createE(); }
			break;




	}
}

Model::~Model() {}


void Model::createR() {
	SceneNode* node;

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, 0.0f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, 0.0f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 1.65f, 0.0f));
	addChild(node);


	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, 1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, 1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(1.4f, 0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(1.4f, 1.65f, 0.0f));
	addChild(node);


	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, -37.5f));
	node->translate(glm::vec3(-0.475f, -0.90f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, -37.5f));
	node->translate(glm::vec3(0.47f, -1.65f, 0.0f));
	addChild(node);

}

void Model::createA() {
	SceneNode* node;

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, 0.0f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, 0.0f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, 1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, 1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(1.4f, 0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(1.4f, 1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(1.4f, -0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(1.4f, -1.65f, 0.0f));
	addChild(node);

}



void Model::createI() {
	SceneNode* node;

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(0.0f, 0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(0.0f, 1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(0.0f, -0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(0.0f, -1.65f, 0.0f));
	addChild(node);
}


void Model::createL() {
	SceneNode* node;

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, -1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, -1.9f, 0.0f));
	addChild(node);

}


void Model::createE() {
	SceneNode* node;

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, 0.0f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, 0.0f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, 1.65f, 0.0f));
	addChild(node);


	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -0.55f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->rotate(glm::vec3(0.0f, 0.0f, 90.0f));
	node->translate(glm::vec3(-1.4f, -1.65f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, -1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, -1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(-0.55f, 1.9f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 0.25f));
	node->translate(glm::vec3(0.55f, 1.9f, 0.0f));
	addChild(node);
}












// Methods used in assignment 1

void Model::createN() {
	SceneNode* node;

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
	SceneNode* node;

	node = new SceneNode(cube);
	node->scale(glm::vec3(2.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 4.5f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 4.25f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->shear(glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(3.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->scale(glm::vec3(1.0f, 2.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.5, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.5f, 0.5, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 0.75f, 0.0f));
	addChild(node);

	node = new SceneNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 4.25f, 0.0f));
	addChild(node);
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
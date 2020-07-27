#include "Model.h"

Model::Model(char c) {
	cube = new Cube;
	sphere = new Sphere(3.0, 5);

	bottomPart = new GroupNode;
	addChild(bottomPart);

	topPart = new GroupNode;
	topPart->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(topPart);

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
	node = new DrawNode(cube);
	node->translate(glm::vec3(-0.5f, 0.75f, 0.0f));
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, -1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 2.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->translate(glm::vec3(0.5f, 1.75f, 0.0f));
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, -1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 2.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	bottomPart->addChild(node);




	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 1.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 1.25f, 0.0f));
	bottomPart->addChild(node);



	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 1.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 1.25f, 0.0f));
	bottomPart->addChild(node);

}

void Model::create1() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(0.0f, 1.25f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(0.0f, 1.25f, 0.0f));
	topPart->addChild(node);


	node = new DrawNode(cube);
	node->scale(glm::vec3(1.25f, 1.0f, 1.0f));
	node->translate(glm::vec3(-1.125, 1.5f, 0.0f));
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	topPart->addChild(node);
}

void Model::createH() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(2.0f, 0.5, 1.0f));
	node->translate(glm::vec3(0.0f, 2.25f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(2.0f, 0.5, 1.0f));
	node->translate(glm::vec3(0.0f, 0.25f, 0.0f));
	topPart->addChild(node);


	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 1.25f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 1.25f, 0.0f));
	topPart->addChild(node);


	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 1.25f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 1.25f, 0.0f));
	topPart->addChild(node);
}
void Model::create5() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 0.5f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.0f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 0.5f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.25f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 0.5f, 1.0f));
	node->translate(glm::vec3(0.0f, 0.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->translate(glm::vec3(-1.5f, 1.0f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->translate(glm::vec3(1.5f, 1.5f, 0.0f));
	bottomPart->addChild(node);

}

void Model::create2() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(2.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.0f, 2.0f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 1.75f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(1.5f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->translate(glm::vec3(0.75f, 0.5, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(1.5f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->translate(glm::vec3(-0.75f, 2.0, 0.0f));
	bottomPart->addChild(node);


	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.5f, 0.5, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 0.75f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 1.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 1.75f, 0.0f));
	topPart->addChild(node);
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
	node->translate(glm::vec3(0.5f, 1.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 0.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 0.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 2.25f, 0.0f));
	bottomPart->addChild(node);



	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 1.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(-1.5f, 1.25f, 0.0f));
	bottomPart->addChild(node);


	node = new DrawNode(cube);
	node->setManualTransform(glm::mat4(
		glm::vec4(1.0f, 1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		));
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(0.5f, 1.25f, 0.0f));
	bottomPart->addChild(node);
}

void Model::create3() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 1.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(1.0f, 2.5f, 1.0f));
	node->translate(glm::vec3(1.5f, 1.25f, 0.0f));
	bottomPart->addChild(node);


	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 0.5f, 0.0f));
	bottomPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 0.5f, 1.0f));
	node->translate(glm::vec3(-0.5f, 0.25f, 0.0f));
	topPart->addChild(node);

	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 0.5f, 1.0f));
	node->translate(glm::vec3(-0.5f, 2.25f, 0.0f));
	bottomPart->addChild(node);


	node = new DrawNode(cube);
	node->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	node->translate(glm::vec3(-0.5f, 2.0f, 0.0f));
	topPart->addChild(node);
}


void Model::setColours(glm::vec3 newColour) {
	cube->setColours(newColour);
}


void Model::pitchForward(float pitch) {
	topPart->rotate(glm::vec3(-pitch, 0.0f, 0.0f));
}

void Model::pitchBackward(float pitch) {
	topPart->rotate(glm::vec3(pitch, 0.0f, 0.0f));
}
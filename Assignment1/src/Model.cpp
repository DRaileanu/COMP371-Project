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

	//add cases for each letter/digit here and create your own function


	}
}

Model::~Model() {

}

void Model::createN() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	transform = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0, 1.0f));
	transform = transform * glm::mat4(
		glm::vec4(1.0f, -1.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	node->setTransform(transform);
	addChild(node);

	node = new SceneNode(cube);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.0f,5.0f, 1.0f));
	node->setTransform(transform);
	addChild(node);

	node = new SceneNode(cube);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.0f, 5.0f, 1.0f));
	node->setTransform(transform);
	addChild(node);
	
}

void Model::create1() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 5.0f, 1.0f));
	node->setTransform(transform);
	addChild(node);

	node = new SceneNode(cube);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.125, 1.5f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.25f, 1.0f, 1.0f));
	transform = transform * glm::mat4(
		glm::vec4(1.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	node->setTransform(transform);
	addChild(node);
}

void Model::createH() {
	SceneNode* node;
	glm::mat4 transform;

	node = new SceneNode(cube);
	transform = glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	transform = glm::scale(transform, glm::vec3(2.0f, 1.0, 1.0f));
	node->setTransform(transform);
	addChild(node);

	node = new SceneNode(cube);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.0f, 5.0f, 1.0f));
	node->setTransform(transform);
	addChild(node);

	node = new SceneNode(cube);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.0f, 5.0f, 1.0f));
	node->setTransform(transform);
	addChild(node);
}
void Model::create5() {
	SceneNode* node;
	glm::mat4 transform;
	transform = glm::mat4(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)

	);
	node = new SceneNode(cube);
	transform = glm::scale(transform, glm::vec3(4.0f, 1.0f, 1.0f));
	node->setTransform(transform);
	addChild(node);

	transform = glm::mat4(1.0f);
	node = new SceneNode(cube);
	transform = glm::scale(transform, glm::vec3(4.0f, 1.0f, 1.0f));
	transform = glm::translate(transform, glm::vec3(0.0f, 2.0f, 0.0f));
	node->setTransform(transform);
	addChild(node);

	transform = glm::mat4(1.0f);
	node = new SceneNode(cube);
	transform = glm::scale(transform, glm::vec3(4.0f, 1.0f, 1.0f));
	transform = glm::translate(transform, glm::vec3(0.0f, -2.0f, 0.0f));
	node->setTransform(transform);
	addChild(node);

	//just a unit cube for the 5
	transform = glm::mat4(1.0f);
	node = new SceneNode(cube);
	transform = glm::translate(transform, glm::vec3(-1.5f, 1.0f, 0.0f));
	node->setTransform(transform);
	addChild(node);

	transform = glm::mat4(1.0f);
	node = new SceneNode(cube);
	transform = glm::translate(transform, glm::vec3(1.5f, -1.0f, 0.0f));
	node->setTransform(transform);
	addChild(node);

	/*node = new SceneNode(cube);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.125f, 1.375f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.25f, 1.0f, 1.0f));
	node->setTransform(transform);
	addChild(node);*/
}
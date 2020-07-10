#include "SceneNode.h"

SceneNode::SceneNode(Drawable* drawable) {
	this->drawable = drawable;
	parent = NULL;
	localTransform = glm::mat4(1.0f);
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scaling = glm::vec3(1.0f, 1.0f, 1.0f);
	shearing = glm::mat4(1.0f);
}

SceneNode::~SceneNode() {
	for (auto child : children) {
		delete child;
	}
	//TODO leaving uncommented causes memory leak i think, will test later
	//if (mesh != NULL) {
	//	delete mesh;
	//	mesh = NULL;
	//}
}

void SceneNode::draw() {
	if (drawable) {
		drawable->draw();
	}
}

void SceneNode::updateLocalTransform(float dt) {
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scaling);
	transform = transform * shearing;
	localTransform = transform;

}

void SceneNode::updateWorldTransform(float dt) {
	updateLocalTransform(dt);
	if (parent) {//node has parent
		worldTransform = parent->worldTransform * localTransform;
	}
	else {//node is root node
		worldTransform = localTransform;
	}
	for (auto child : children) {
		child->updateWorldTransform(dt);
	}
}

void SceneNode::addChild(SceneNode* child) {
	children.push_back(child);
	child->parent = this;
}

void SceneNode::translate(glm::vec3 t) {
	translation += t;
}

void SceneNode::scale(glm::vec3 s) {
	scaling = s*scaling;
}

void SceneNode::rotate(glm::vec3 r) {
	rotation += r;
}

void SceneNode::shear(glm::mat4 shear) {
	shearing = shear;
}
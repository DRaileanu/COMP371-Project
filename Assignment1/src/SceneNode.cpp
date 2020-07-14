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
	if (drawable != NULL) {
		delete drawable;
		drawable = NULL;
	}
}

//draws the drawable mesh if it exists
void SceneNode::draw() {
	if (drawable) {
		drawable->draw();
	}
}

// computes local transform using transformaiton parameters in order shear->->scale->rotate(ZYX)->translate
void SceneNode::updateLocalTransform() {
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scaling);
	transform = transform * shearing;
	localTransform = transform;

}

// recursively update scene node's world transform relative to parent's
void SceneNode::updateWorldTransform() {
	updateLocalTransform();
	if (parent) {//node has parent
		worldTransform = parent->worldTransform * localTransform;
	}
	else {//node is root node
		worldTransform = localTransform;
	}
	for (auto child : children) {
		child->updateWorldTransform();
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

// note just sets shear, so can't stack several shears. Consider as initial manual transform before any others
void SceneNode::shear(glm::mat4 shear) {
	shearing = shear;
}

void SceneNode::setRotation(glm::vec3 r) {
	rotation = r;
}
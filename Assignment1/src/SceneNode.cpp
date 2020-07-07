#include "SceneNode.h"

SceneNode::SceneNode(Mesh* mesh) {
	this->mesh = mesh;
	parent = NULL;
	localTransform = glm::mat4(1.0f);
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

void SceneNode::addChild(SceneNode* child) {
	children.push_back(child);
	child->parent = this;
}

void SceneNode::draw() {
	if (mesh) {
		mesh->draw();
	}
}

void SceneNode::update(float dt) {
	if (parent) {//node has parent
		worldTransform = parent->worldTransform * localTransform;
	}
	else {//node is root node
		worldTransform = localTransform;
	}
	for (auto child : children) {
		child->update(dt);
	}
}
#include "SceneNode.h"

SceneNode::SceneNode() {
	localTransform = glm::mat4(1.0f);
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scaling = glm::vec3(1.0f, 1.0f, 1.0f);
	manualTransform = glm::mat4(1.0f);
	dirty = true;
}

SceneNode::~SceneNode() {
	//for (auto child : children) {
	//	delete child;
	//}
	//if (drawable != NULL) {
	//	delete drawable;
	//	drawable = NULL;
	//}
}

//draws the drawable mesh if it exists
//void SceneNode::draw() {
//	if (drawable) {
//		drawable->draw();
//	}
//}

// computes local transform using transformaiton parameters in order shear->->scale->rotate(ZYX)->translate
void SceneNode::updateLocalTransform() {
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scaling);
	transform = transform * manualTransform;
	localTransform = transform;

}

// recursively update scene node's world transform relative to parent's
void SceneNode::updateWorldTransform(const glm::mat4& CTM) {
	if (dirty) {//replace dirty with true to see FPS difference
		updateLocalTransform();
		dirty = false;
	}
	worldTransform = CTM * localTransform;
}

//void SceneNode::addChild(SceneNode* child) {
//	children.push_back(child);
//	child->parent = this;
//}

//void SceneNode::removeChild(SceneNode* child) {
//	children.erase(std::find(children.begin(), children.end(), child));
//}


void SceneNode::setTranslation(glm::vec3 t) {
	translation = t;
	dirty = true;
}

void SceneNode::setRotation(glm::vec3 r) {
	rotation = r;
	dirty = true;
}

void SceneNode::setScaling(glm::vec3 s) {
	scaling = s;
	dirty = true;
}

void SceneNode::setManualTransform(glm::mat4 m) {
	manualTransform = m;
	dirty = true;
}


void SceneNode::translate(glm::vec3 t) {
	translation += t;
	dirty = true;
}

void SceneNode::scale(glm::vec3 s) {
	scaling = s*scaling;
	dirty = true;
}

void SceneNode::rotate(glm::vec3 r) {
	rotation += r;
	dirty = true;
}
void SceneNode::moveForward(glm::vec3 t) {
	int cycles = rotation.y / 360;
	//std::cout << cycles;
	float degrees = rotation.y - (cycles * 360);
	float dx = (std::sin(glm::radians(degrees)));
	float dz = (std::cos(glm::radians(degrees)));//sin(degrees)
	t.x = dx;
	t.z = dz;
	translation += t;
	dirty = true;
	std::cout << t.z;
	//std::cout <<"rotation.y: "<<rotation.y <<"cycles: "<<cycles <<"degrees: "<< degrees <<"\n";
	//std::cout <<"angle now is: "<< rotation.x << " " << rotation.y << " " << rotation.z;

}
void SceneNode::moveBackwards(glm::vec3 t) {
	int cycles = rotation.y / 360;
	//std::cout << cycles;
	float degrees = rotation.y - (cycles * 360);
	float dx = (std::sin(glm::radians(degrees)))/-1;
	float dz = (std::cos(glm::radians(degrees)))/-1;//sin(degrees)
	t.x = dx;
	t.z = dz;
	translation += t;
	dirty = true;
	std::cout << t.z;
	//std::cout <<"rotation.y: "<<rotation.y <<"cycles: "<<cycles <<"degrees: "<< degrees <<"\n";
	//std::cout <<"angle now is: "<< rotation.x << " " << rotation.y << " " << rotation.z;

}

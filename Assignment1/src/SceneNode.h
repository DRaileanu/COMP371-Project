#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Drawable.h"
#include <vector>

class SceneNode {
public:
	SceneNode(Drawable* drawable = NULL);
	~SceneNode();

	virtual void draw();
	virtual void updateLocalTransform(float dt);
	virtual void updateWorldTransform(float dt);

	void addChild(SceneNode*);
	std::vector<SceneNode*> getChildren() { return children; }

	Drawable* getDrawable() const { return drawable; }
	void setDrawable(Drawable* drawable) { this->drawable = drawable; }

	//const glm::mat4& getTransform() const { return localTransform; }
	//void setTransform(const glm::mat4& matrix) { localTransform = matrix; }
	glm::mat4 getWorldTransform() const { return worldTransform; }
	
	void translate(glm::vec3);
	void scale(glm::vec3);
	void rotate(glm::vec3);
	void shear(glm::mat4);

protected:
	SceneNode*	parent;
	Drawable*	drawable;
	glm::mat4	worldTransform;
	glm::mat4	localTransform;
	std::vector<SceneNode*> children;

private:
	glm::vec3	translation;
	glm::vec3	rotation;
	glm::vec3	scaling;
	glm::mat4	shearing;
};


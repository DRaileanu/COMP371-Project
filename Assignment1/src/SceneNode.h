//---------------------------------------------------------------------------------------------------------------------
// While the implementation of this class is authentic, the general structure was highly inspired from:
// JMonkeyEngine Scene Graph for Dummies https://wiki.jmonkeyengine.org/tutorials/scenegraph/assets/fallback/index.html
// OpenSceneGraph https://codedocs.xyz/openscenegraph/OpenSceneGraph/annotated.html
//---------------------------------------------------------------------------------------------------------------------

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Drawable.h"
#include <vector>

//base class for nodes in a Scene Graph
//holds pointer to its Drawable geometry to draw it and provides implementation for basic geometry manipulation via rotate, scale and translate

class SceneNode {
public:
	SceneNode(Drawable* drawable = NULL);
	virtual ~SceneNode();

	virtual void draw();
	virtual void updateLocalTransform();
	virtual void updateWorldTransform();

	void addChild(SceneNode*);
	std::vector<SceneNode*> getChildren() { return children; }

	Drawable* getDrawable() const { return drawable; }
	void setDrawable(Drawable* drawable) { this->drawable = drawable; }

	glm::mat4 getWorldTransform() const { return worldTransform; }
	
	//used to update localTransform
	void translate(glm::vec3);
	void scale(glm::vec3);
	void rotate(glm::vec3);//input is rotation along xyz-axes in degrees. Rotations are applied in order: ZYX
	void shear(glm::mat4);//will only apply initial shear before any transformations, applying shear to already shear'd SceneNode will simply set new shear
	
	void setRotation(glm::vec3);//manually set rotation


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


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

//enum class SceneNodeType {
//	GroupNode,
//	DrawNode,
//	LightNode
//};


class SceneNode {
public:
	virtual ~SceneNode();

	//virtual SceneNodeType nodeType() const = 0;
	//get transform parameters
	const glm::vec3 getTranslation() { return translation; }
	const glm::vec3 getRotation() { return rotation; }
	const glm::vec3 getScaling() { return scaling; }
	const glm::mat4 getManualTransform() { return manualTransform; }
	//set transform parameters
	void setTranslation(glm::vec3 t);
	void setRotation(glm::vec3 r);
	void setScaling(glm::vec3 s);
	void setManualTransform(glm::mat4 m);
	//add to current transform parameters
	void translate(glm::vec3);
	void scale(glm::vec3);
	void rotate(glm::vec3);//input is rotation along xyz-axes in degrees. Rotations are applied in order: ZYX
	
	const glm::mat4& getWorldTransform() { return worldTransform; }




	//virtual void draw();
	void updateWorldTransform(const glm::mat4& CTM);

	//void addChild(SceneNode*);
	//void removeChild(SceneNode*);
	//std::vector<SceneNode*> getChildren() { return children; }

	//Drawable* getDrawable() const { return drawable; }
	//void setDrawable(Drawable* drawable) { this->drawable = drawable; }

	bool isDirty() { return dirty; }
	

protected:
	SceneNode();//not allowed to instantiate SceneNode on their own, must be a derived class
	void updateLocalTransform();

	//SceneNode*	parent;
	//Drawable*	drawable;
	glm::mat4	worldTransform;
	glm::mat4	localTransform;
	//std::vector<SceneNode*> children;

	glm::vec3	translation;
	glm::vec3	rotation;
	glm::vec3	scaling;
	glm::mat4	manualTransform;

	bool dirty;//used to know if localTransform needs to be updated to improve performance
	bool visible;
};


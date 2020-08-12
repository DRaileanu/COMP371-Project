//---------------------------------------------------------------------------------------------------------------------
// While the implementation of this class is authentic, the general structure was highly inspired from:
// JMonkeyEngine Scene Graph for Dummies https://wiki.jmonkeyengine.org/tutorials/scenegraph/assets/fallback/index.html
// OpenSceneGraph https://codedocs.xyz/openscenegraph/OpenSceneGraph/annotated.html
// SceneView https://ashuang.github.io/sceneview/index.html
//---------------------------------------------------------------------------------------------------------------------

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Drawable.h"
#include <vector>

//base class for nodes in a Scene Graph. Cannot be instantiated on it's own, use derived classes
//the class is meant to provide the basic topology functions used in a SceneGraph

class SceneNode {
public:
	virtual ~SceneNode();

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
	
	void moveForward(float amount);//move in -z direction relative to local axis
	void moveBackwards(float amount);//move in z direction relative to local axis
	void strafeLeft(float amount);//move in -x direction relative to local axis
	void strafeRight(float amount);//move in x direction relative to local axis


	//worldTransformation
	const glm::mat4& getWorldTransform() { return worldTransform; }
	void updateWorldTransform(const glm::mat4& CTM);

	bool isDirty() { return dirty; }//optimization to avoid recomputing localTransform if hasn't changed since last frame
	

protected:
	SceneNode();//not allowed to instantiate SceneNode on their own, must be a derived class
	virtual void updateLocalTransform();

	glm::mat4	worldTransform;
	glm::mat4	localTransform;

	glm::vec3	translation;
	glm::vec3	rotation;
	glm::quat	quatrotation;
	glm::vec3	scaling;
	glm::mat4	manualTransform;

	bool dirty;//used to know if localTransform needs to be updated to improve performance
};


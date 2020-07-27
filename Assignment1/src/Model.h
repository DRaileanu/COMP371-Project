#pragma once
#include "GroupNode.h"
#include "DrawNode.h"
#include "Cube.h"
#include "Sphere.h"
#include <vector>

//creates models of 3D letters/digits by manipulating geometry of unit cubes

class Model : public GroupNode {
public:
	Model() = delete;
	Model(char);//requires a character to be created
	~Model();

	void setColours(glm::vec3);

	void pitchForward(float pitch);
	void pitchBackward(float pitch);

private:
	//available models
	void createN();
	void create1();
	void createH();
	void create5();
	void create2();
	void createD();
	void create3();

	Drawable* cube;//all DrawNodes of a Model will share same Cube
	Sphere* sphere;
	GroupNode* topPart;
	GroupNode* bottomPart;


};


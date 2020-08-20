#pragma once
#include "GroupNode.h"
#include "DrawNode.h"
#include "Cube.h"
#include "Sphere.h"
#include <vector>

//creates models of 3D letters/digits by manipulating geometry of unit cubes and a sphere
//model has top and bottom part, where top part can be controled individually using appropriate functions

class BorderLines : public GroupNode {
public:
	BorderLines() = delete;//requires a character to be created
	BorderLines(char);
	~BorderLines();

	//methods to set Material/Texture for all DrawNodes under this Model
	void setMaterial(Material*);
	void setTexture(GLuint);

	//methods that control the topPart of model
	void pitchForward(float pitch);
	void pitchBackward(float pitch);
	void shearRight(float shear);
	void shearLeft(float shear);
	void scaleTop(float scale);
	void moveSideToSide(float dt);
	void moveSideToSide2(float dt);
	void moveUpAndDown(float dt);


private:
	//available models
	void createTop();
	void createBottom();
	void createRight();
	void createLeft();

	int i = 0;
	int j = 0;

	int x = 0;
	int y = 0;

	bool firsti = true;
	bool firstx = true;

	Drawable* cube;//all DrawNodes of a Model will share same Cube
	Sphere* sphere;
	GroupNode* topPart;
	GroupNode* bottomPart;

};


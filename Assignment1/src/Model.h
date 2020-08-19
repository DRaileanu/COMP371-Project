#pragma once
#include "GroupNode.h"
#include "DrawNode.h"
#include "Cube.h"
#include "Sphere.h"
#include <vector>

//creates models of 3D letters/digits by manipulating geometry of unit cubes and a sphere
//model has top and bottom part, where top part can be controled individually using appropriate functions

class Model : public GroupNode {
public:
	Model() = delete;//requires a character to be created
	Model(char);
	~Model();

	//methods to set Material/Texture for all DrawNodes under this Model
	void setMaterial(Material*);
	void setTexture(GLuint);

	//methods that control the topPart of model
	//void pitchForward(float pitch);
	//void pitchBackward(float pitch);
	//void shearRight(float shear);
	//void shearLeft(float shear);
	//void scaleTop(float scale);

private:
	//available models
	//void createN();
	void create0();
	//void createH();
	//void create5();
	//void create2();
	//void createD();
	//void create3();

	Drawable* cube;//all DrawNodes of a Model will share same Cube
	Sphere* sphere;
	GroupNode* model;

};


#pragma once
#include "SceneNode.h"
#include "Cube.h"
#include <vector>

//creates models of 3D letters/digits by manipulating geometry of unit cubes

class Model : public SceneNode {
public:
	Model() = delete;
	Model(char);//requires a character to be created
	~Model();

	void setColours(glm::vec3);

private:
	//available models
	void createN();
	void create1();
	void createH();
	void create5();
	void create2();
	void createD();
	void create3();

	Drawable* cube;
};


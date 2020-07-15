#pragma once
#include "SceneNode.h"
#include "Cube.h"
#include <vector>

//creates models of 3D letters/digits by manipulating geometry of unit cubes
// For QUIZ1, note that every cube is scaled by (1.0f, 0.5f, 0.25f) inside createR/A/I/L/E methods as required

class Model : public SceneNode {
public:
	Model() = delete;
	Model(char c, glm::vec3 colour);//requires a character and colour to be created
	~Model();

private:
	//available models
	void createN();
	void create1();
	void createH();
	void create5();
	void create2();
	void createD();
	void create3();

	//new models added for Quiz1
	void createR();
	void createA();
	void createI();
	void createL();
	void createE();

	Drawable* cube;
};


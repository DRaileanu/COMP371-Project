#pragma once
#include "SceneNode.h"
#include "Cube.h"
#include <vector>

class Model : public SceneNode {
public:
	Model() = delete;
	Model(char);
	~Model();



private:
	void createN();
	void create1();
	void createH();
	void create5();
	void create2();

	Drawable* cube;
};


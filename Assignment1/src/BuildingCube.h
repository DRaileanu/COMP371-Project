#pragma once
#include "Drawable.h"

// creates an "empty" cube

class BuildingCube : public Drawable {
public:
	BuildingCube();
	~BuildingCube();

protected:
	virtual void draw();
};


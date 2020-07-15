#pragma once
#include "Drawable.h"

class BuildingCube : public Drawable {
public:
	BuildingCube();
	~BuildingCube();

protected:
	virtual void draw();
};


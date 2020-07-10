#pragma once
#include "Drawable.h"

class Grid : public Drawable {
public:
	Grid(int size = 100);
	~Grid();
	virtual void draw();
};


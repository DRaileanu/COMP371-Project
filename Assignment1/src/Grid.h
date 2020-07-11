#pragma once
#include "Drawable.h"

//creates square grid of size*size number of squares

class Grid : public Drawable {
public:
	Grid(int size = 100);
	~Grid();
	virtual void draw();
};


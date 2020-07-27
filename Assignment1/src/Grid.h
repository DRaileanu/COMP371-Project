#pragma once
#include "Drawable.h"

//creates square grid of size*size number of squares

class Grid : public Drawable {
public:
	Grid();
	~Grid();

private:
	void addSquare(float x, float z);
};


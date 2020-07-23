#pragma once
#include "Drawable.h"

class AxisLines : public Drawable {
public:
	AxisLines();
	~AxisLines();

protected:
	void draw() override;
};


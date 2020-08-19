#pragma once
#include "GroupNode.h"
#include "DrawNode.h"
#include "Model.h"

class Timer : public GroupNode
{
public:
	Timer();
	~Timer() {};
	Model* column;
	Model* leftMinute;
	Model* rightMinute;
	Model* leftSecond;
	Model* rightSecond;
};
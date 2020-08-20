#pragma once
#include "GroupNode.h"
#include "DrawNode.h"
#include "Model.h"
#include <time.h>

class Timer : public GroupNode
{
private:
	unsigned long begTime;
public:
	void gameStart();
	void start() {
		begTime = clock();
	};
	unsigned long elapsedTime() {
		return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	};
	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	};

	Timer();
	~Timer() {};
	Model* column;
	Model* leftMinute;
	Model* rightMinute;
	Model* leftSecond;
	Model* rightSecond;

};
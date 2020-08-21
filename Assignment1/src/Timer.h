#pragma once


#include "GroupNode.h"
#include "DrawNode.h"
#include "Model.h"
#include <time.h>


class Timer : public GroupNode
{
private:
	unsigned long begTime = 0;
public:
	void start() {
		begTime = clock();
	}
	unsigned long elapsedTime() {
		return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	};
	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	};
	void stop();
	void timeUpdate(unsigned long elapsedTime,bool timeStarted);
	void updateRightSecond();
	void updateLeftSecond();
	void updateRightMinute();
	void updateLeftMinute();
	void reset();
	char getModelChar(int);

	Timer();
	~Timer() {};
	Model* column;
	Model* leftMinute;
	Model* rightMinute;
	Model* leftSecond;
	Model* rightSecond;

	int rightSecond_int;
	int leftSecond_int;
	int rightMinute_int;
	int leftMinute_int;
	int current_seconds;
	bool timeStarted;

};
#include "Timer.h"

Timer::Timer() {
	column = new Model(':');
	addChild(column);

	leftMinute = new Model('0');
	rightMinute = new Model('0');
	leftSecond = new Model('1');
	rightSecond = new Model('0');

	int rightSecond_int = 0;
	leftMinute->translate(glm::vec3(-5.5f, 0.0f, 0.0f));
	addChild(leftMinute);

	rightMinute->translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	addChild(rightMinute);
	leftSecond->translate(glm::vec3(2.0f, 0.0f, 0.0f));
	addChild(leftSecond);
	rightSecond->translate(glm::vec3(5.5f, 0.0f, 0.0f));
	addChild(rightSecond);
	current_seconds = 0;
	timeStarted = false;
}
void Timer::timeUpdate(unsigned long elapsedTime,bool timeStarted) {
	if (timeStarted) {
		if (elapsedTime > (unsigned long)current_seconds) {
			current_seconds++;
			rightSecond_int++;
			updateRightSecond();
			std::cout << current_seconds;
		}
	}
}
void Timer::updateRightSecond() {
	char newModelChar = getModelChar(rightSecond_int);
	//delete rightSecond;
}
char Timer::getModelChar(int number) {
	switch (number) {
	case 0: {return '0'; }
		  break;
	case 1: {return '1'; }
		  break;
	case 2: {return '2'; }

	case 3: {return '3'; }
		  break;

	case 4: {return '4'; }
		  break;
	case 5: {return '5'; }
		  break;
	case 6: {return '6'; }
		  break;
	case 7: {return '7'; }
		  break;
	case 8: {return '8'; }
		  break;

	case 9: {return '9'; }
		  break;

	}
}
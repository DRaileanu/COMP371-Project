#include "Timer.h"

Timer::Timer() {
	column = new Model(':');
	addChild(column);

	leftMinute = new Model('0');
	rightMinute = new Model('0');
	leftSecond = new Model('0');
	rightSecond = new Model('0');

	rightSecond_int = 0;
	leftSecond_int = 0;
	leftMinute_int = 0;
	rightMinute_int = 0;

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
void Timer::stop() {
	timeStarted = false;
	current_seconds = 0;
}
void Timer:: reset() {
	leftMinute->~Model();
	rightMinute->~Model();
	leftSecond->~Model();
	rightSecond->~Model();

	rightSecond_int = 0;
	leftSecond_int = 0;
	leftMinute_int = 0;
	rightMinute_int = 0;

	leftMinute = new Model('0');
	leftMinute->translate(glm::vec3(-5.5f, 0.0f, 0.0f));
	addChild(leftMinute);
	rightMinute = new Model('0');
	rightMinute->translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	addChild(rightMinute);
	leftSecond = new Model('0');
	leftSecond->translate(glm::vec3(2.0f, 0.0f, 0.0f));
	addChild(leftSecond);
	rightSecond = new Model('0');
	rightSecond->translate(glm::vec3(5.5f, 0.0f, 0.0f));
	addChild(rightSecond);
	timeStarted = false;
	current_seconds = 0;
}
void Timer::timeUpdate(unsigned long elapsedTime,bool timeStarted) {
	if (timeStarted) {
		if (elapsedTime > (unsigned long)current_seconds) {
			current_seconds++;
			updateRightSecond();
			std::cout << current_seconds;
		}
	}
}
void Timer::updateRightSecond() {
	if (rightSecond_int == 9) {
		rightSecond_int = 0;
		updateLeftSecond();
	}
	else {
		rightSecond_int++;
	}
	char newModelChar = getModelChar(rightSecond_int);
	rightSecond->~Model();
	rightSecond = new Model(newModelChar);
	rightSecond->translate(glm::vec3(5.5f, 0.0f, 0.0f));
	addChild(rightSecond); 

}

void Timer::updateLeftSecond() {
	if (leftSecond_int == 5) {
		leftSecond_int = 0;
		updateRightMinute();
	}
	else {
		leftSecond_int++;
	}
	char newModelChar = getModelChar(leftSecond_int);
	leftSecond->~Model();
	leftSecond = new Model(newModelChar);
	leftSecond->translate(glm::vec3(2.0f, 0.0f, 0.0f));
	addChild(leftSecond);	

}

void Timer::updateRightMinute() {
	if (rightMinute_int == 9) {
		rightMinute_int = 0;
		updateLeftMinute();
	}
	else {
		rightMinute_int++;
	}
	char newModelChar = getModelChar(rightMinute_int);
	rightMinute->~Model();
	rightMinute = new Model(newModelChar);
	rightMinute->translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	addChild(rightMinute);
}

void Timer::updateLeftMinute() {
	if (leftMinute_int == 5) {
		leftMinute_int = 0;
	}
	else {
		leftMinute_int++;
	}
	char newModelChar = getModelChar(leftMinute_int);
	leftMinute->~Model();
	leftMinute = new Model(newModelChar);
	leftMinute->translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	addChild(leftMinute);
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
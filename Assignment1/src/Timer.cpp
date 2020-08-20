#include "Timer.h"

Timer::Timer() {
	column = new Model(':');
	addChild(column);
	leftMinute = new Model('0');
	rightMinute = new Model('0');
	leftSecond = new Model('0');
	rightSecond = new Model('0');
	leftMinute->translate(glm::vec3(-5.5f, 0.0f, 0.0f));
	addChild(leftMinute);
	rightMinute->translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	addChild(rightMinute);
	leftSecond->translate(glm::vec3(2.0f, 0.0f, 0.0f));
	addChild(leftSecond);
	rightSecond->translate(glm::vec3(5.5f, 0.0f, 0.0f));
	addChild(rightSecond);
}
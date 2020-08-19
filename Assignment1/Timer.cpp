#include "Timer.h"

Timer::Timer() {
	leftMinute = new Model('0');
	std::cout << "created model";
	leftMinute->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	addChild(leftMinute);
}
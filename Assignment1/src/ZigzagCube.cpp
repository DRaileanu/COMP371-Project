#include "ZigzagCube.h"




ZigzagCube::ZigzagCube(float w, float d) : width(w), depth(d), cube(), direction(nz) {
	DrawNode* cubeNode = new DrawNode(&cube);
	color = RandUnitVec();
	cube.setColours(color);
	cubeNode->scale(glm::vec3(0.25, 0.25, 0.25));
	cubeNode->translate(glm::vec3(0.0, 0.25, 0.0));
	addChild(cubeNode);

		
	int xPos = RandRange(-width + 10, width - 10);
	int zPos = RandRange(-depth + 10, depth - 10);
	glm::vec3 initialPos = glm::vec3(xPos, 0.0f, zPos);
	setTranslation(initialPos);
	keyframe1Pos = initialPos;
	updateKeyframe2();
	updateDirection();
}


void ZigzagCube::animationUpdate(float dt) {
	keyframeTime += dt;
	if (keyframeTime >= animDuration) {
		keyframeTime = animDuration;
		lastKeyframe = true;
	}

	glm::vec3 updatedPos = glm::mix(keyframe1Pos, keyframe2Pos, keyframeTime / animDuration);
	setTranslation(updatedPos);


	if (lastKeyframe) {
		keyframeTime = 0.0f;
		lastKeyframe = false;
		keyframe1Pos = keyframe2Pos;
		updateDirection();
		updateKeyframe2();

	}
}


void ZigzagCube::updateDirection() {
	float rand = RandRange(0, 100);
	switch (direction) {
	case px:
		if (abs(keyframe2Pos.x) == width) {
			direction = nx;	
		}
		else {
			if (rand < 60) { direction = px; }
			else { 
				if (rand < 80) {
					direction = pz;
				}
				else {
					direction = nz;
				}
			}
		}
		break;
	case nx:
		if (abs(keyframe2Pos.x) == width) {
			direction = px;
		}
		else {
			if (rand < 60) { direction = nx; }
			else { 
				if (rand < 80) {
					direction = pz;
				}
				else {
					direction = nz;
				}
			}
		}
		break;
	case pz:
		if (abs(keyframe2Pos.z) == depth) {
			direction = nz;
		}
		else {
			if (rand < 60) { direction = pz; }
			else {
				if (rand < 80) {
					direction = px;
				}
				else {
					direction = nx;
				}
			}
		}
		break;
	case nz:
		if (abs(keyframe2Pos.z) == depth) {
			direction = pz;
		}
		else {
			if (rand < 60) { direction = nz; }
			else {
				if (rand < 80) {
					direction = px;
				}
				else {
					direction = nx;
				}
			}
		}
		break;
	}
}

void ZigzagCube::updateKeyframe2() {
	glm::vec3 movementDirection;
	switch (direction) {
	case px:
		movementDirection = glm::vec3(1.0, 0.0f, 0.0f);
		break;
	case nx:
		movementDirection = glm::vec3(-1.0, 0.0f, 0.0f);
		break;
	case pz:
		movementDirection = glm::vec3(0.0, 0.0f, 1.0f);
		break;
	case nz:
		movementDirection = glm::vec3(0.0, 0.0f, -1.0f);
		break;
	}
	keyframe2Pos = keyframe1Pos + movementDirection;
}

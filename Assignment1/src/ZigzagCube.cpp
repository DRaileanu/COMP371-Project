#include "ZigzagCube.h"




ZigzagCube::ZigzagCube(float w, float d) : width(w), depth(d), cube(), pEffect(100), direction(nz) {
	DrawNode* cubeNode = new DrawNode(&cube);
	cubeNode->scale(glm::vec3(0.5, 0.5, 0.5));
	cubeNode->translate(glm::vec3(0.0, 0.25, 0.0));
	addChild(cubeNode);

	pEffectNode = new DrawNode(&pEffect);
	pEffectNode->translate(glm::vec3(0.0, 0.25, 0.0f));
	addChild(pEffectNode);

	
	static ParticleEmitter particleEmitter;
	particleEmitter.MaxWidth = 0.01f;
	particleEmitter.MinWidth = -0.01f;
	particleEmitter.MaxHeight = 0.01f;
	particleEmitter.MinHeight = -0.01f;
	particleEmitter.MaxDepth = 0.5f;
	particleEmitter.MinDepth = 0.0f;
	particleEmitter.MaxSpeed = 2.5;
	particleEmitter.MinSpeed = 0.8;
	particleEmitter.MaxLifetime = 0.25;
	particleEmitter.MinLifetime = 0.75;


	pEffect.setRotateAxis(glm::vec3(0.25, 0.5, 0.75));
	pEffect.setRotateKeyFrames(0.0f, 90.0f);
	pEffect.setSizeKeyFrames(0.050, 0.025);
	pEffect.setColorKeyFrames(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	pEffect.SetParticleEmitter(&particleEmitter);



	
	int xPos = RandRange(-width + 10, width - 10);
	int zPos = RandRange(-depth + 10, depth - 10);
	glm::vec3 initialPos = glm::vec3(xPos, 0.0f, zPos);
	setTranslation(initialPos);
	keyframe1Pos = initialPos;
	updateKeyframe2();
	updateDirection();
}


void ZigzagCube::animationUpdate(float dt) {
	pEffect.Update(dt);
	static float keyframeTime = 0.0f;
	static bool lastKeyframe = false;
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
			pEffectNode->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		}
		else {
			if (rand < 50) { direction = px; }
			else { 
				if (rand < 75) {
					direction = pz;
					pEffectNode->rotate(glm::vec3(0.0f, -90.0f, 0.0f));
				}
				else {
					direction = nz;
					pEffectNode->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
				}
			}
		}
		break;
	case nx:
		if (abs(keyframe2Pos.x) == width) {
			direction = px;
			pEffectNode->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		}
		else {
			if (rand < 50) { direction = nx; }
			else { 
				if (rand < 75) {
					direction = pz;
					pEffectNode->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
				}
				else {
					direction = nz;
					pEffectNode->rotate(glm::vec3(0.0f, -90.0f, 0.0f));
				}
			}
		}
		break;
	case pz:
		if (abs(keyframe2Pos.z) == depth) {
			direction = nz;
			pEffectNode->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		}
		else {
			if (rand < 50) { direction = pz; }
			else {
				if (rand < 75) {
					direction = px;
					pEffectNode->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
				}
				else {
					direction = nx;
					pEffectNode->rotate(glm::vec3(0.0f, -90.0f, 0.0f));
				}
			}
		}
		break;
	case nz:
		if (abs(keyframe2Pos.z) == depth) {
			direction = pz;
			pEffectNode->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
		}
		else {
			if (rand < 50) { direction = nz; }
			else {
				if (rand < 75) {
					direction = px;
					pEffectNode->rotate(glm::vec3(0.0f, -90.0f, 0.0f));
				}
				else {
					direction = nx;
					pEffectNode->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
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

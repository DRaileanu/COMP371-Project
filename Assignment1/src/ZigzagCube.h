#pragma once
#include "GroupNode.h"
#include "DrawNode.h"
#include "Cube.h"
#include "ParticleEffect.h"
#include "Random.h"
#include <math.h>

class ZigzagCube : public GroupNode {
	enum Direction { px, pz, nx, nz };// p/n for positive/negative along an axis
public:
	ZigzagCube(float width, float depth);
	~ZigzagCube() {}

	void update(const glm::mat4& CTM, float dt) override {
		animationUpdate(dt);
		updateWorldTransform(CTM);
	}


private:
	void animationUpdate(float dt);
	void updateKeyframe2();
	void updateDirection();

	float width;
	float depth;
	Cube cube;
	ParticleEffect pEffect;
	DrawNode* pEffectNode;

	float animDuration = 0.2;
	glm::vec3 keyframe1Pos;
	glm::vec3 keyframe2Pos;
	Direction direction;

};


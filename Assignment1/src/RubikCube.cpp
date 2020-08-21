#include "RubikCube.h"

extern irrklang::ISoundEngine* SoundEngine;
RubikCube::RubikCube() {
	animated = false;
	animationDuration = 0.7f;
	//setup all the rubikParts
	GroupNode* rubikPart;

	//1,1,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, -1.0f, 1.0f));
	rubikParts[std::make_tuple(1, 1, 1)] = rubikPart;
	addChild(rubikPart);
	//1,1,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, -1.0f, 0.0f));
	rubikParts[std::make_tuple(1, 1, 2)] = rubikPart;
	addChild(rubikPart);
	//1,1,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, -1.0f, -1.0f));
	rubikParts[std::make_tuple(1, 1, 3)] = rubikPart;
	addChild(rubikPart);
	//1,2,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, 0.0f, 1.0f));
	rubikParts[std::make_tuple(1, 2, 1)] = rubikPart;
	addChild(rubikPart);
	//1,2,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, 0.0f, 0.0f));
	rubikParts[std::make_tuple(1, 2, 2)] = rubikPart;
	addChild(rubikPart);
	//1,2,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, 0.0f, -1.0f));
	rubikParts[std::make_tuple(1, 2, 3)] = rubikPart;
	addChild(rubikPart);
	//1,3,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, 1.0f, 1.0f));
	rubikParts[std::make_tuple(1, 3, 1)] = rubikPart;
	addChild(rubikPart);
	//1,3,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, 1.0f, 0.0f));
	rubikParts[std::make_tuple(1, 3, 2)] = rubikPart;
	addChild(rubikPart);
	//1,3,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(-1.0f, 1.0f, -1.0f));
	rubikParts[std::make_tuple(1, 3, 3)] = rubikPart;
	addChild(rubikPart);
	//2,1,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, -1.0f, 1.0f));
	rubikParts[std::make_tuple(2, 1, 1)] = rubikPart;
	addChild(rubikPart);
	//2,1,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, -1.0f, 0.0f));
	rubikParts[std::make_tuple(2, 1, 2)] = rubikPart;
	addChild(rubikPart);
	//2,1,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, -1.0f, -1.0f));
	rubikParts[std::make_tuple(2, 1, 3)] = rubikPart;
	addChild(rubikPart);
	//2,2,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, 0.0f, 1.0f));
	rubikParts[std::make_tuple(2, 2, 1)] = rubikPart;
	addChild(rubikPart);
	//2,2,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	rubikParts[std::make_tuple(2, 2, 2)] = rubikPart;
	addChild(rubikPart);
	//2,2,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, 0.0f, -1.0f));
	rubikParts[std::make_tuple(2, 2, 3)] = rubikPart;
	addChild(rubikPart);
	//2,3,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, 1.0f, 1.0f));
	rubikParts[std::make_tuple(2, 3, 1)] = rubikPart;
	addChild(rubikPart);
	//2,3,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, 1.0f, 0.0f));
	rubikParts[std::make_tuple(2, 3, 2)] = rubikPart;
	addChild(rubikPart);
	//2,3,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(0.0f, 1.0f, -1.0f));
	rubikParts[std::make_tuple(2, 3, 3)] = rubikPart;
	addChild(rubikPart);
	//3,1,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, -1.0f, 1.0f));
	rubikParts[std::make_tuple(3, 1, 1)] = rubikPart;
	addChild(rubikPart);
	//3,1,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, -1.0f, 0.0f));
	rubikParts[std::make_tuple(3, 1, 2)] = rubikPart;
	addChild(rubikPart);
	//3,1,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, -1.0f, -1.0f));
	rubikParts[std::make_tuple(3, 1, 3)] = rubikPart;
	addChild(rubikPart);
	//3,2,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, 0.0f, 1.0f));
	rubikParts[std::make_tuple(3, 2, 1)] = rubikPart;
	addChild(rubikPart);
	//3,2,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, 0.0f, 0.0f));
	rubikParts[std::make_tuple(3, 2, 2)] = rubikPart;
	addChild(rubikPart);
	//3,2,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, 0.0f, -1.0f));
	rubikParts[std::make_tuple(3, 2, 3)] = rubikPart;
	addChild(rubikPart);
	//3,3,1
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, 1.0f, 1.0f));
	rubikParts[std::make_tuple(3, 3, 1)] = rubikPart;
	addChild(rubikPart);
	//3,3,2
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, 1.0f, 0.0f));
	rubikParts[std::make_tuple(3, 3, 2)] = rubikPart;
	addChild(rubikPart);
	//3,3,3
	rubikPart = new GroupNode;
	rubikPart->translate(glm::vec3(1.0f, 1.0f, -1.0f));
	rubikParts[std::make_tuple(3, 3, 3)] = rubikPart;
	addChild(rubikPart);


}



void RubikCube::update(const glm::mat4& CTM, float dt) {
	if (animated) {
		animationUpdate();
	}
	updateWorldTransform(CTM);
}


/*
	Handles animation by updating the animationNodes using the animationRotation
	Updates propertionally to how much time passed since last update divided by animationDuration
*/
void RubikCube::animationUpdate() {
	static bool animationInProgress = false;
	static float animationStartFrame = glfwGetTime();
	static float lastFrame = glfwGetTime();
	
	if (!animationInProgress) {//first time function is called, we simply mark that we are going to start animation starting from next frame
		animationInProgress = true;
		lastFrame = animationStartFrame = glfwGetTime();
	}
	else {
		float currentFrame = glfwGetTime();
		float dt;

		if (animationStartFrame + animationDuration <= currentFrame) {//if time elapsed since start of animation is longer than animationDuration, we manually set dt so that we don't overshot the rotation
			dt = animationStartFrame + animationDuration - lastFrame;
			animationInProgress = false;
			animated = false;
		}
		else {
			dt = currentFrame - lastFrame;
		}
		lastFrame = currentFrame;


		//update all animationNodes
		glm::vec3 deltaRotation = (dt / animationDuration) * animationRotation;
		glm::quat rotationQuaternion(glm::radians(deltaRotation));
		rotationQuaternion = glm::normalize(rotationQuaternion);
		glm::mat4 rotationMatrix = glm::mat4_cast(rotationQuaternion);
		for (auto& animNode : animationNodes) {
			animNode->rotate(rotationMatrix);//rotates the mini-cube relative to it's own center
			//because all mini-cubes are translated relative to the center of the cube, rotating the translation matrix results in rotating about the RubikCube axes
			glm::vec3 translation = animNode->getTranslation();
			//glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
			//glm::mat4 rotatedTranslationMatrix = rotationMatrix * translationMatrix;
			//glm::vec3 rotatedTranslation = glm::vec3(rotatedTranslationMatrix[3]);
			animNode->setTranslation(translation * glm::conjugate(rotationQuaternion));
		}
		
		
	}
	
	//for testing by performing rotation 1 in frame
	/*
	glm::vec3 deltaRotation = animationRotation;
	glm::quat rotationQuaternion(glm::radians(deltaRotation));
	glm::mat4 rotationMatrix = glm::mat4_cast(rotationQuaternion);
	for (auto& animNode : animationNodes) {
		animNode->rotate(rotationMatrix);

		glm::vec3 translation = animNode->getTranslation();
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 rotatedTranslationMatrix = rotationMatrix * translationMatrix;
		glm::vec3 rotatedTranslation = glm::vec3(rotatedTranslationMatrix[3]);
		animNode->setTranslation(rotatedTranslation);

	}
	animated = false;
	*/

}



//Methods to setup the animation for RubikCube. They place the appropriate RubikParts inside animatedNodes and update the RubikParts coordinates to how they will look like after animation is complete

void RubikCube::rotatePositiveXCW() {
	if (!animated) {//only do the setup when called without any animation in progress
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		//fill the animationNodes and get a copy of all nodes inside temp to do the swapping after
		for (int y = 1; y <= 3; ++y) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int,int,int> coord(3, y, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(-90.0f, 0.0f, 0.0f);

		rubikParts.at(std::make_tuple(3, 1, 1)) = temp[std::make_tuple(3, 1, 3)];
		rubikParts.at(std::make_tuple(3, 1, 2)) = temp[std::make_tuple(3, 2, 3)];
		rubikParts.at(std::make_tuple(3, 1, 3)) = temp[std::make_tuple(3, 3, 3)];
		rubikParts.at(std::make_tuple(3, 2, 1)) = temp[std::make_tuple(3, 1, 2)];
		rubikParts.at(std::make_tuple(3, 2, 3)) = temp[std::make_tuple(3, 3, 2)];
		rubikParts.at(std::make_tuple(3, 3, 1)) = temp[std::make_tuple(3, 1, 1)];
		rubikParts.at(std::make_tuple(3, 3, 2)) = temp[std::make_tuple(3, 2, 1)];
		rubikParts.at(std::make_tuple(3, 3, 3)) = temp[std::make_tuple(3, 3, 1)];

	}

}

void RubikCube::rotatePositiveXCCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int y = 1; y <= 3; ++y) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int, int, int> coord(3, y, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(90.0f, 0.0f, 0.0f);

		rubikParts.at(std::make_tuple(3, 1, 1)) = temp[std::make_tuple(3, 3, 1)];
		rubikParts.at(std::make_tuple(3, 1, 2)) = temp[std::make_tuple(3, 2, 1)];
		rubikParts.at(std::make_tuple(3, 1, 3)) = temp[std::make_tuple(3, 1, 1)];
		rubikParts.at(std::make_tuple(3, 2, 1)) = temp[std::make_tuple(3, 3, 2)];
		rubikParts.at(std::make_tuple(3, 2, 3)) = temp[std::make_tuple(3, 1, 2)];
		rubikParts.at(std::make_tuple(3, 3, 1)) = temp[std::make_tuple(3, 3, 3)];
		rubikParts.at(std::make_tuple(3, 3, 2)) = temp[std::make_tuple(3, 2, 3)];
		rubikParts.at(std::make_tuple(3, 3, 3)) = temp[std::make_tuple(3, 1, 3)];

	}
}

void RubikCube::rotateNegativeXCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int y = 1; y <= 3; ++y) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int, int, int> coord(1, y, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(90.0f, 0.0f, 0.0f);

		rubikParts.at(std::make_tuple(1, 1, 1)) = temp[std::make_tuple(1, 3, 1)];
		rubikParts.at(std::make_tuple(1, 1, 2)) = temp[std::make_tuple(1, 2, 1)];
		rubikParts.at(std::make_tuple(1, 1, 3)) = temp[std::make_tuple(1, 1, 1)];
		rubikParts.at(std::make_tuple(1, 2, 1)) = temp[std::make_tuple(1, 3, 2)];
		rubikParts.at(std::make_tuple(1, 2, 3)) = temp[std::make_tuple(1, 1, 2)];
		rubikParts.at(std::make_tuple(1, 3, 1)) = temp[std::make_tuple(1, 3, 3)];
		rubikParts.at(std::make_tuple(1, 3, 2)) = temp[std::make_tuple(1, 2, 3)];
		rubikParts.at(std::make_tuple(1, 3, 3)) = temp[std::make_tuple(1, 1, 3)];

	}
}

void RubikCube::rotateNegativeXCCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int y = 1; y <= 3; ++y) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int, int, int> coord(1, y, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(-90.0f, 0.0f, 0.0f);

		rubikParts.at(std::make_tuple(1, 1, 1)) = temp[std::make_tuple(1, 1, 3)];
		rubikParts.at(std::make_tuple(1, 1, 2)) = temp[std::make_tuple(1, 2, 3)];
		rubikParts.at(std::make_tuple(1, 1, 3)) = temp[std::make_tuple(1, 3, 3)];
		rubikParts.at(std::make_tuple(1, 2, 1)) = temp[std::make_tuple(1, 1, 2)];
		rubikParts.at(std::make_tuple(1, 2, 3)) = temp[std::make_tuple(1, 3, 2)];
		rubikParts.at(std::make_tuple(1, 3, 1)) = temp[std::make_tuple(1, 1, 1)];
		rubikParts.at(std::make_tuple(1, 3, 2)) = temp[std::make_tuple(1, 2, 1)];
		rubikParts.at(std::make_tuple(1, 3, 3)) = temp[std::make_tuple(1, 3, 1)];

	}
}

void RubikCube::rotatePositiveYCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int, int, int> coord(x, 3, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, -90.0f, 0.0f);

		rubikParts.at(std::make_tuple(1, 3, 1)) = temp[std::make_tuple(3, 3, 1)];
		rubikParts.at(std::make_tuple(1, 3, 2)) = temp[std::make_tuple(2, 3, 1)];
		rubikParts.at(std::make_tuple(1, 3, 3)) = temp[std::make_tuple(1, 3, 1)];
		rubikParts.at(std::make_tuple(2, 3, 1)) = temp[std::make_tuple(3, 3, 2)];
		rubikParts.at(std::make_tuple(2, 3, 3)) = temp[std::make_tuple(1, 3, 2)];
		rubikParts.at(std::make_tuple(3, 3, 1)) = temp[std::make_tuple(3, 3, 3)];
		rubikParts.at(std::make_tuple(3, 3, 2)) = temp[std::make_tuple(2, 3, 3)];
		rubikParts.at(std::make_tuple(3, 3, 3)) = temp[std::make_tuple(1, 3, 3)];

	}
}

void RubikCube::rotatePositiveYCCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int, int, int> coord(x, 3, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, 90.0f, 0.0f);

		rubikParts.at(std::make_tuple(1, 3, 1)) = temp[std::make_tuple(1, 3, 3)];
		rubikParts.at(std::make_tuple(1, 3, 2)) = temp[std::make_tuple(2, 3, 3)];
		rubikParts.at(std::make_tuple(1, 3, 3)) = temp[std::make_tuple(3, 3, 3)];
		rubikParts.at(std::make_tuple(2, 3, 1)) = temp[std::make_tuple(1, 3, 2)];
		rubikParts.at(std::make_tuple(2, 3, 3)) = temp[std::make_tuple(3, 3, 2)];
		rubikParts.at(std::make_tuple(3, 3, 1)) = temp[std::make_tuple(1, 3, 1)];
		rubikParts.at(std::make_tuple(3, 3, 2)) = temp[std::make_tuple(2, 3, 1)];
		rubikParts.at(std::make_tuple(3, 3, 3)) = temp[std::make_tuple(3, 3, 1)];

	}
}

void RubikCube::rotateNegativeYCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int, int, int> coord(x, 1, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, 90.0f, 0.0f);

		rubikParts.at(std::make_tuple(1, 1, 1)) = temp[std::make_tuple(1, 1, 3)];
		rubikParts.at(std::make_tuple(1, 1, 2)) = temp[std::make_tuple(2, 1, 3)];
		rubikParts.at(std::make_tuple(1, 1, 3)) = temp[std::make_tuple(3, 1, 3)];
		rubikParts.at(std::make_tuple(2, 1, 1)) = temp[std::make_tuple(1, 1, 2)];
		rubikParts.at(std::make_tuple(2, 1, 3)) = temp[std::make_tuple(3, 1, 2)];
		rubikParts.at(std::make_tuple(3, 1, 1)) = temp[std::make_tuple(1, 1, 1)];
		rubikParts.at(std::make_tuple(3, 1, 2)) = temp[std::make_tuple(2, 1, 1)];
		rubikParts.at(std::make_tuple(3, 1, 3)) = temp[std::make_tuple(3, 1, 1)];

	}
}

void RubikCube::rotateNegativeYCCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int z = 1; z <= 3; ++z) {
				std::tuple<int, int, int> coord(x, 1, z);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, -90.0f, 0.0f);

		rubikParts.at(std::make_tuple(1, 1, 1)) = temp[std::make_tuple(3, 1, 1)];
		rubikParts.at(std::make_tuple(1, 1, 2)) = temp[std::make_tuple(2, 1, 1)];
		rubikParts.at(std::make_tuple(1, 1, 3)) = temp[std::make_tuple(1, 1, 1)];
		rubikParts.at(std::make_tuple(2, 1, 1)) = temp[std::make_tuple(3, 1, 2)];
		rubikParts.at(std::make_tuple(2, 1, 3)) = temp[std::make_tuple(1, 1, 2)];
		rubikParts.at(std::make_tuple(3, 1, 1)) = temp[std::make_tuple(3, 1, 3)];
		rubikParts.at(std::make_tuple(3, 1, 2)) = temp[std::make_tuple(2, 1, 3)];
		rubikParts.at(std::make_tuple(3, 1, 3)) = temp[std::make_tuple(1, 1, 3)];

	}
}

void RubikCube::rotatePositiveZCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int y = 1; y <= 3; ++y) {
				std::tuple<int, int, int> coord(x, y, 1);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, 0.0f, -90.0f);

		rubikParts.at(std::make_tuple(1, 1, 1)) = temp[std::make_tuple(3, 1, 1)];
		rubikParts.at(std::make_tuple(2, 1, 1)) = temp[std::make_tuple(3, 2, 1)];
		rubikParts.at(std::make_tuple(3, 1, 1)) = temp[std::make_tuple(3, 3, 1)];
		rubikParts.at(std::make_tuple(1, 2, 1)) = temp[std::make_tuple(2, 1, 1)];
		rubikParts.at(std::make_tuple(3, 2, 1)) = temp[std::make_tuple(2, 3, 1)];
		rubikParts.at(std::make_tuple(1, 3, 1)) = temp[std::make_tuple(1, 1, 1)];
		rubikParts.at(std::make_tuple(2, 3, 1)) = temp[std::make_tuple(1, 2, 1)];
		rubikParts.at(std::make_tuple(3, 3, 1)) = temp[std::make_tuple(1, 3, 1)];

	}
}

void RubikCube::rotatePositiveZCCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int y = 1; y <= 3; ++y) {
				std::tuple<int, int, int> coord(x, y, 1);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, 0.0f, 90.0f);

		rubikParts.at(std::make_tuple(1, 1, 1)) = temp[std::make_tuple(1, 3, 1)];
		rubikParts.at(std::make_tuple(2, 1, 1)) = temp[std::make_tuple(1, 2, 1)];
		rubikParts.at(std::make_tuple(3, 1, 1)) = temp[std::make_tuple(1, 1, 1)];
		rubikParts.at(std::make_tuple(1, 2, 1)) = temp[std::make_tuple(2, 3, 1)];
		rubikParts.at(std::make_tuple(3, 2, 1)) = temp[std::make_tuple(2, 1, 1)];
		rubikParts.at(std::make_tuple(1, 3, 1)) = temp[std::make_tuple(3, 3, 1)];
		rubikParts.at(std::make_tuple(2, 3, 1)) = temp[std::make_tuple(3, 2, 1)];
		rubikParts.at(std::make_tuple(3, 3, 1)) = temp[std::make_tuple(3, 1, 1)];

	}
}

void RubikCube::rotateNegativeZCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int y = 1; y <= 3; ++y) {
				std::tuple<int, int, int> coord(x, y, 3);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, 0.0f, 90.0f);

		rubikParts.at(std::make_tuple(1, 1, 3)) = temp[std::make_tuple(1, 3, 3)];
		rubikParts.at(std::make_tuple(2, 1, 3)) = temp[std::make_tuple(1, 2, 3)];
		rubikParts.at(std::make_tuple(3, 1, 3)) = temp[std::make_tuple(1, 1, 3)];
		rubikParts.at(std::make_tuple(1, 2, 3)) = temp[std::make_tuple(2, 3, 3)];
		rubikParts.at(std::make_tuple(3, 2, 3)) = temp[std::make_tuple(2, 1, 3)];
		rubikParts.at(std::make_tuple(1, 3, 3)) = temp[std::make_tuple(3, 3, 3)];
		rubikParts.at(std::make_tuple(2, 3, 3)) = temp[std::make_tuple(3, 2, 3)];
		rubikParts.at(std::make_tuple(3, 3, 3)) = temp[std::make_tuple(3, 1, 3)];

	}
}

void RubikCube::rotateNegativeZCCW() {
	if (!animated) {
		animated = true;
		SoundEngine->play2D("audio/turn.mp3");

		animationNodes.clear();
		std::map<std::tuple<int, int, int>, GroupNode*> temp;
		for (int x = 1; x <= 3; ++x) {
			for (int y = 1; y <= 3; ++y) {
				std::tuple<int, int, int> coord(x, y, 3);
				GroupNode* node = rubikParts[coord];
				animationNodes.push_back(node);
				temp[coord] = node;
			}
		}
		animationRotation = glm::vec3(0.0f, 0.0f, -90.0f);

		rubikParts.at(std::make_tuple(1, 1, 3)) = temp[std::make_tuple(3, 1, 3)];
		rubikParts.at(std::make_tuple(2, 1, 3)) = temp[std::make_tuple(3, 2, 3)];
		rubikParts.at(std::make_tuple(3, 1, 3)) = temp[std::make_tuple(3, 3, 3)];
		rubikParts.at(std::make_tuple(1, 2, 3)) = temp[std::make_tuple(2, 1, 3)];
		rubikParts.at(std::make_tuple(3, 2, 3)) = temp[std::make_tuple(2, 3, 3)];
		rubikParts.at(std::make_tuple(1, 3, 3)) = temp[std::make_tuple(1, 1, 3)];
		rubikParts.at(std::make_tuple(2, 3, 3)) = temp[std::make_tuple(1, 2, 3)];
		rubikParts.at(std::make_tuple(3, 3, 3)) = temp[std::make_tuple(1, 3, 3)];

	}
}


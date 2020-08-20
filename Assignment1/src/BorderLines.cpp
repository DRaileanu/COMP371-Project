#include "BorderLines.h"
#include <glm/gtx/transform2.hpp>


BorderLines::BorderLines(char c) {
	cube = new Cube;


	bottomPart = new GroupNode;
	addChild(bottomPart);

	topPart = new GroupNode;
	topPart->translate(glm::vec3(0.0f, 2.5f, 0.0f));
	addChild(topPart);


	switch (c) {
	case 'T': {createTop(); }
			break;
	case 'B': {createBottom(); }
			break;
	case 'R': {createRight(); }
			break;
	case 'L': {createLeft(); }
			break;
	}
}

BorderLines::~BorderLines() {
	delete cube;
}


void BorderLines::createTop() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 0.1, 1.0f));
	node->translate(glm::vec3(0.0f, 2.0f, 0.0f));
	bottomPart->addChild(node);


}

void BorderLines::createBottom() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 0.1, 1.0f));
	node->translate(glm::vec3(0.0f, -2.0f, 0.0f));
	bottomPart->addChild(node);


}

void BorderLines::createRight() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 0.1, 1.0f));
	node->translate(glm::vec3(0.0f, 3.0f, 0.0f));
	bottomPart->addChild(node);


}

void BorderLines::createLeft() {
	DrawNode* node;

	node = new DrawNode(cube);
	node->scale(glm::vec3(4.0f, 0.1, 1.0f));
	node->translate(glm::vec3(0.0f, -3.0f, 0.0f));
	bottomPart->addChild(node);

}


//void Model::setColours(glm::vec3 newColour) {
//	cube->setColours(newColour);
//}


//using lambda recursion, sets material for all DrawNodes under this Model
//I'm actually amazed that this worked lol
void BorderLines::setMaterial(Material* material) {
	auto traversal = [&](SceneNode* node)->void {
		auto lambda = [&](SceneNode* node, const auto& lambda)->void {
			if (DrawNode* drawNode = dynamic_cast<DrawNode*>(node)) {
				drawNode->setMaterial(material);
				return;
			}
			else if (GroupNode* groupNode = dynamic_cast<GroupNode*>(node)) {
				for (SceneNode* child : groupNode->getChildren()) {
					lambda(child, lambda);
				}
			}
			else return;
		};
		return lambda(node, lambda);
	};
	traversal(this);

}
//using lambda recursion, sets textures for all DrawNodes under this Model
void BorderLines::setTexture(GLuint tex) {
	auto traversal = [&](SceneNode* node)->void {
		auto lambda = [&](SceneNode* node, const auto& lambda)->void {
			if (DrawNode* drawNode = dynamic_cast<DrawNode*>(node)) {
				drawNode->setTexture(tex);
				return;
			}
			else if (GroupNode* groupNode = dynamic_cast<GroupNode*>(node)) {
				for (SceneNode* child : groupNode->getChildren()) {
					lambda(child, lambda);
				}
			}
			else return;
		};
		return lambda(node, lambda);
	};
	traversal(this);
}


void BorderLines::pitchForward(float pitch) {
	topPart->rotate(glm::vec3(-pitch, 0.0f, 0.0f));
}

void BorderLines::pitchBackward(float pitch) {
	topPart->rotate(glm::vec3(pitch, 0.0f, 0.0f));
}

void BorderLines::shearRight(float shear) {
	glm::mat4 matr = topPart->getManualTransform();
	matr = glm::shearY3D(matr, -shear, 0.0f);
	topPart->setManualTransform(matr);
}

void BorderLines::shearLeft(float shear) {
	glm::mat4 matr = topPart->getManualTransform();
	matr = glm::shearY3D(matr, shear, 0.0f);
	topPart->setManualTransform(matr);
}

void BorderLines::scaleTop(float scale) {
	topPart->scale(glm::vec3(1.0f, 1 + scale, 1.0f));
}

void BorderLines::moveSideToSide(float dt) {
	if (firsti) {
		i = 100;
		firsti = false;
	}

	i++;
	if (i < 150) {
		this->strafeLeft(25 * dt);
	}
	else {

		j++;
		if (j < 150) {
			
			this->strafeRight(25 * dt);

		}
		else {
			i = 0;
			j = 0;
		}

	}
}

void BorderLines::moveSideToSide2(float dt) {
	if (firstx) {
		i = 100;
		firstx = false;
	}

	i++;
	if (i < 150) {
		this->strafeRight(25 * dt);
	}
	else {

		j++;
		if (j < 150) {

			this->strafeLeft(25 * dt);

		}
		else {
			i = 0;
			j = 0;
		}

	}
}


void BorderLines::moveUpAndDown(float dt) {
	if (firstx) {
		x = 32;
		firstx = false;
	}
	x++;
	if (x < 50) {
	    this->moveDown(25 * dt);
	}
	else {
	    y++;
	    if (y < 50) {
	        this->moveUp(25 * dt);
	    }
	    else {
	        x = 0;
	        y = 0;
	    }
	}
}



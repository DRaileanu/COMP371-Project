#include "RubikCube.h"

RubikCube::RubikCube() {
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


	//setup the DrawNodes and Quads for all rubikParts
	//all Quads facing towards +z, coordinates (x,y,1)
	for (int x = 1; x <= 3; ++x) {
		for (int y = 1; y <= 3; ++y) {
			rubikPart = rubikParts[std::make_tuple(x, y, 1)];
			Drawable* quad = new Quad;
			quad->setColours(glm::vec3(1.0f, 0.0f, 0.0f));
			DrawNode* quadNode = new DrawNode(quad);
			quadNode->translate(glm::vec3(0.0f, 0.0f, 0.5f));
			rubikPart->addChild(quadNode);
		}
	}
	//all Quads facing towards -z, coordinates (x,y,3)
	for (int x = 1; x <= 3; ++x) {
		for (int y = 1; y <= 3; ++y) {
			rubikPart = rubikParts[std::make_tuple(x, y, 3)];
			Drawable* quad = new Quad;
			quad->setColours(glm::vec3(1.0f, 1.0f, 0.0f));
			DrawNode* quadNode = new DrawNode(quad);
			quadNode->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
			quadNode->translate(glm::vec3(0.0f, 0.0f, -0.5f));
			rubikPart->addChild(quadNode);
		}
	}
	//all Quads facing towards +x, coordinates (3,y,z)
	for (int y = 1; y <= 3; ++y) {
		for (int z = 1; z <= 3; ++z) {
			rubikPart = rubikParts[std::make_tuple(3, y, z)];
			Drawable* quad = new Quad;
			quad->setColours(glm::vec3(1.0f, 0.0f, 1.0f));
			DrawNode* quadNode = new DrawNode(quad);
			quadNode->rotate(glm::vec3(0.0f, 90.0f, 0.0f));
			quadNode->translate(glm::vec3(0.5f, 0.0f, 0.0f));
			rubikPart->addChild(quadNode);
		}
	}
	//all Quads facing towards -x, coordinates (1,y,z)
	for (int y = 1; y <= 3; ++y) {
		for (int z = 1; z <= 3; ++z) {
			rubikPart = rubikParts[std::make_tuple(1, y, z)];
			Drawable* quad = new Quad;
			quad->setColours(glm::vec3(0.0f, 1.0f, 0.0f));
			DrawNode* quadNode = new DrawNode(quad);
			quadNode->rotate(glm::vec3(0.0f, -90.0f, 0.0f));
			quadNode->translate(glm::vec3(-0.5f, 0.0f, 0.0f));
			rubikPart->addChild(quadNode);
		}
	}
	//all Quads facing towards +y, coordinates (x,3,z)
	for (int x = 1; x <= 3; ++x) {
		for (int z = 1; z <= 3; ++z) {
			rubikPart = rubikParts[std::make_tuple(x, 3, z)];
			Drawable* quad = new Quad;
			quad->setColours(glm::vec3(0.0f, 1.0f, 1.0f));
			DrawNode* quadNode = new DrawNode(quad);
			quadNode->rotate(glm::vec3(-90.0f, 0.0f, 0.0f));
			quadNode->translate(glm::vec3(0.0f, 0.5f, 0.0f));
			rubikPart->addChild(quadNode);
		}
	}
	//all Quads facing towards -y, coordinates (x,1,z)
	for (int x = 1; x <= 3; ++x) {
		for (int z = 1; z <= 3; ++z) {
			rubikPart = rubikParts[std::make_tuple(x, 1, z)];
			Drawable* quad = new Quad;
			quad->setColours(glm::vec3(0.0f, 0.0f, 1.0f));
			DrawNode* quadNode = new DrawNode(quad);
			quadNode->rotate(glm::vec3(90.0f, 0.0f, 0.0f));
			quadNode->translate(glm::vec3(0.0f, -0.5f, 0.0f));
			rubikPart->addChild(quadNode);
		}
	}


}


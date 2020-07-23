#include "GroupNode.h"


void GroupNode::addChild(SceneNode* child) {
	children.push_back(child);
}

void GroupNode::removeChild(SceneNode* child) {
	children.erase(std::find(children.begin(), children.end(), child));
}

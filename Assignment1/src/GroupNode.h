#pragma once
#include "SceneNode.h"

//Only SceneNode that is allowed to have children. Use to provide SceneGraph topology

class GroupNode : public SceneNode {
public:
	GroupNode() {};
	~GroupNode() {
		for (auto child : children) delete child;
	}

	void addChild(SceneNode*child) {
		children.push_back(child);
	}

	//TODO add removeChild() if needed. Can't just itirate through children, since some may be GroupNode with their own children

	std::vector<SceneNode*> getChildren() { return children; }

protected:
	std::vector<SceneNode*> children;
};


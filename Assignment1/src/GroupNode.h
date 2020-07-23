#pragma once
#include "SceneNode.h"

class GroupNode : public SceneNode {
public:
	GroupNode() {};
	~GroupNode() {
		for (auto child : children) delete child;
	}

	void addChild(SceneNode*);
	void removeChild(SceneNode*);

	std::vector<SceneNode*> getChildren() { return children; }

private:
	std::vector<SceneNode*> children;
};


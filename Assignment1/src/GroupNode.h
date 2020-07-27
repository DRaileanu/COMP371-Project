#pragma once
#include "SceneNode.h"

class GroupNode : public SceneNode {
public:
	GroupNode() {};
	~GroupNode() {
		for (auto child : children) delete child;
	}

	virtual void addChild(SceneNode*);
	virtual void removeChild(SceneNode*);

	std::vector<SceneNode*> getChildren() { return children; }

protected:
	std::vector<SceneNode*> children;
};


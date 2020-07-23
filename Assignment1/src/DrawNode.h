#pragma once
#include "SceneNode.h"
#include "Drawable.h"

class DrawNode : public SceneNode {
public:
	DrawNode() {}
	DrawNode(Drawable* d) { drawable = d; }
	~DrawNode() {}

	Drawable* getDrawable() { return drawable; }
	void setDrawable(Drawable* d) { drawable = d; }

	void draw() {
		if (drawable) {
			drawable->draw();
		}
	}

	GLuint getTexture() { return texture; }
	void setTexture(GLuint tex) { texture = tex; }

	bool isTransparent() { return transparent; }
	void setTransparent(bool t) { transparent = t; }

private:
	Drawable* drawable;
	GLuint texture;
	bool transparent;
};


#pragma once
#include "SceneNode.h"
#include "Drawable.h"

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class DrawNode : public SceneNode {
public:
	//DrawNode() {}
	DrawNode(Drawable* d) : drawable(d), material{ glm::vec3(0.24725, 0.2245, 0.0645), glm::vec3(0.34615, 0.3143, 0.0903), glm::vec3(0.797357, 0.723991, 0.208006), 83.2f } {}
	~DrawNode() {}

	Drawable* getDrawable() { return drawable; }
	void setDrawable(Drawable* d) { drawable = d; }

	void draw() {
		if (drawable) {
			drawable->draw();
		}
	}

	Material getMaterial() { return material; }
	void setMaterial(Material m) { material = m; }

	GLuint getTexture() { return texture; }
	void setTexture(GLuint tex) { texture = tex; }

	bool isTransparent() { return transparent; }
	void setTransparent(bool t) { transparent = t; }

private:
	Drawable* drawable;
	Material material;
	GLuint texture;
	bool transparent;
};


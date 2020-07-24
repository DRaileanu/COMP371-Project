#pragma once
#include "SceneNode.h"

enum class LightType {
	DirLight, PointLight, SpotLight
};

class LightNode : public SceneNode {
public:
	LightNode() = delete;
	LightNode(LightType t) {
		type = t;
		//colour = glm::vec3(0.0f, 0.0f, 0.0f);
		ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
		specular = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	~LightNode() {}

	LightType getType() { return type; }
	//glm::vec3 getColour() { return colour; }
	glm::vec3 getAmbient() { return ambient; }
	glm::vec3 getDiffuse() { return diffuse; }
	glm::vec3 getSpecular() { return specular; }

	void setType(LightType t) { type = t; }
	//void setColour(glm::vec3 c) { colour = c; }
	void setAmbient(glm::vec3 a) { ambient = a; }
	void setDiffuse(glm::vec3 d) { diffuse = d; }
	void setSpecular(glm::vec3 s) { specular = s; }


private:
	LightType type;
	//glm::vec3 colour;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	//glm::vec3 direction;//only needed for PointLight and SpotLight
	//float coneAngle;//only needed for SpotLight

};


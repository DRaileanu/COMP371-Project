#pragma once
#include "SceneNode.h"

enum class LightType {
	DirLight, PointLight, SpotLight
};

struct LightProperties {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class LightNode : public SceneNode {
public:
	LightNode() = delete;
	LightNode(LightType t) {
		type = t;
		properties.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		properties.diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
		properties.specular = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	~LightNode() {}

	LightType getType() { return type; }
	LightProperties getProperties() { return properties; }

	void setType(LightType t) { type = t; }
	void setProperties(LightProperties p) { properties = p; }


private:
	LightType type;
	//glm::vec3 colour;
	LightProperties properties;
	//glm::vec3 direction;//only needed for PointLight and SpotLight
	//float coneAngle;//only needed for SpotLight
	

};


// Renderer class that traverses SceneNode recursively to render the scene. Also manages shaders.

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <forward_list>
#include <map>

#include "Camera.h"
#include "GroupNode.h"
#include "DrawNode.h"
#include "Shader.h"
#include "LightNode.h"

extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

class Renderer{
	const static int MAX_LIGHTS = 3;//be sure that it matches the MAX_LIGHTS from shaders
	const static unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
public:
	Renderer(Camera* camera, Shader* genericShader, Shader* blendingShader, Shader* shadowShader);
	~Renderer();

	void updateScene();
	void render();

	void setRootSceneNode(GroupNode* node) { rootSceneNode = node; }
	void removeRootSceneNode() { rootSceneNode = NULL; }

	//drawing parameters
	void setPolygonMode(GLuint mode) { polygonMode = mode; }
	void setTexRatio(float ratio) { texRatio = ratio; }
	void setShadowMode(bool mode) { shadowMode = mode; }

	void postRender();//for benchmarking purposes, remove later. (need to be called after every preRender/render or refilling drawables list with repeating data)

private:

	Shader* genericShader;
	Shader* blendingShader;
	Shader* shadowShader;

	Camera* mainCamera;

	GroupNode* rootSceneNode;
	std::vector<LightNode*> lights;
	std::forward_list<DrawNode*> opaqueDrawables;
	std::map<float, DrawNode*> transparentDrawables;

	GLuint polygonMode;
	float texRatio;
	bool shadowMode;

	GLuint depthMapFBO = 0;//frame buffer for rendering shadows
	GLuint depthCubeMap = 0;//cube depth map texture to hold info for shadow maping Point Lights


	

	void updateNode(SceneNode* node, const glm::mat4& CTM);
	void renderNode(DrawNode* node);
	void shadowRenderNode(DrawNode* node);
	


};


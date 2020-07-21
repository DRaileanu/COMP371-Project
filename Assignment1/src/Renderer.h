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
#include "SceneNode.h"
#include "Shader.h"
#include "Light.h"

extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

class Renderer{
public:
	Renderer(Camera* camera, Shader* genericShader, Shader* blendingShader);
	~Renderer();

	void updateScene(SceneNode*);
	void render();

	void setRootSceneNode(SceneNode*);
	void removeRootSceneNode(SceneNode*);//does not delete the actual SceneNode, just removes from rendering (would probably never be used, consider removing)

	//drawing parameters
	void setPolygonMode(GLuint mode) { polygonMode = mode; }
	void setTexRatio(float ratio) { texRatio = ratio; }

	void postRender();//for benchmarking purposes, remove later. (need to be called after every preRender/render or refilling drawables list with repeating data)

private:

	Shader* genericShader;
	Shader* blendingShader;
	Shader* shadowShader;

	Camera* mainCamera;

	SceneNode* rootSceneNode;
	std::forward_list<Light*> lights;
	std::forward_list<SceneNode*> opaqueDrawables;
	std::map<float, SceneNode*> transparentDrawables;

	GLuint polygonMode;
	float texRatio;

	void renderNode(SceneNode*);




};


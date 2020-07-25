#include "Renderer.h"


Renderer::Renderer(Camera* camera, Shader* genericShader, Shader* blendingShader, Shader* shadowShader) {
	this->mainCamera = camera;
	this->genericShader = genericShader;
	this->blendingShader = blendingShader;
	this->shadowShader = shadowShader;

	polygonMode = GL_TRIANGLES;
	texRatio = 1.0f;
	shadowMode = true;
	
	// configure depthMapFBO
	// -----------------------
	glGenFramebuffers(1, &depthMapFBO);
	// setup depthCubeMap texture
	glGenTextures(1, &depthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
	for (unsigned int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//setup textures
	genericShader->use();
	genericShader->setInt("texture1", 0);
	genericShader->setInt("depthCubeMap", 7);

	blendingShader->use();
	blendingShader->setInt("texture1", 0);
	blendingShader->setInt("depthCubeMap", 7);


}

Renderer::~Renderer() {

}



void Renderer::render() {
	if (!rootSceneNode) {
		return;
	}
	glDepthMask(GL_TRUE);//needs to be set to true before clearing depth buffer, else getting weird issues
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//View-Projection matrix to be given to shaders
	glm::mat4 projection = glm::perspective(glm::radians(mainCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
	glm::mat4 view = mainCamera->GetViewMatrix();
	glm::mat4 VP = projection * view;
	//camera position for specular lighting calculation in fragment shader
	glm::vec3 viewPos = mainCamera->Position;
	
	float near_plane = 0.1f;
	float far_plane = 100.0f;

	
	genericShader->use();
	genericShader->setMat4("VP", VP);
	genericShader->setVec3("viewPos", viewPos);
	genericShader->setFloat("far_plane", far_plane);
	genericShader->setBool("shadows", shadowMode);

	for (int i = 0; i < lights.size(); ++i) {
		switch (lights[i]->getType()) {
		case LightType::PointLight: {
				genericShader->setVec3("pointLights[" + std::to_string(i) + "].position", lights[i]->getWorldTransform()[3]);
				LightProperties properties = lights[i]->getProperties();
				genericShader->setVec3("pointLights[" + std::to_string(i) + "].ambient", properties.ambient);
				genericShader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", properties.diffuse);
				genericShader->setVec3("pointLights[" + std::to_string(i) + "].specular", properties.specular);
				break;
		}
		//TODO add cases for DirLight and SpotLight

		default : {}
		}
	}

	blendingShader->use();
	blendingShader->setMat4("VP", VP);
	blendingShader->setVec3("viewPos", viewPos);
	blendingShader->setFloat("far_plane", far_plane);
	blendingShader->setBool("shadows", shadowMode);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);

	for (int i = 0; i < lights.size(); ++i) {
		switch (lights[i]->getType()) {
		case LightType::PointLight: {
				blendingShader->setVec3("pointLights[" + std::to_string(i) + "].position", lights[i]->getWorldTransform()[3]);
				LightProperties properties = lights[i]->getProperties();
				blendingShader->setVec3("pointLights[" + std::to_string(i) + "].ambient", properties.ambient);
				blendingShader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", properties.diffuse);
				blendingShader->setVec3("pointLights[" + std::to_string(i) + "].specular", properties.specular);
				break;
		}


		default: {}
		}
	}

	if (shadowMode) {
		//create depthCubeMap transformation matrics
		glm::vec3 lightPos = lights[0]->getWorldTransform()[3];
		//float near_plane = 1.0f;
		//float far_plane = 25.0f;
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
		std::vector<glm::mat4> shadowTransforms;
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

		//render scene to depthCubeMap
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		shadowShader->use();
		for (unsigned int i = 0; i < 6; ++i) {
			shadowShader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
		}
		shadowShader->setFloat("far_plane", far_plane);
		shadowShader->setVec3("lightPos", lightPos);

		glEnable(GL_CULL_FACE);
		for (auto& node : opaqueDrawables) {
			shadowRenderNode(node);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}


	// render opaques first
	glDisable(GL_BLEND);//does it really need to be disabled?
	glEnable(GL_CULL_FACE);
	for (auto& node : opaqueDrawables) {
		renderNode(node);
	}

	// render transparents, back to front
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	
	// both methods seem to work the same, consider if theres really a difference since I could swear there was one when i first came up with it

	//method 1
	//--------
	//glDisable(GL_CULL_FACE);
	//for (auto iter = transparentDrawables.rbegin(); iter != transparentDrawables.rend(); ++iter) {
	//	renderNode(iter->second);
	//}

	//method 2
	//--------
	glCullFace(GL_FRONT);
	for (auto iter = transparentDrawables.rbegin(); iter != transparentDrawables.rend(); ++iter) {
		renderNode(iter->second);
	}
	glCullFace(GL_BACK);
	for (auto iter = transparentDrawables.rbegin(); iter != transparentDrawables.rend(); ++iter) {
		renderNode(iter->second);
	}


	//opaqueDrawables.clear();
	//transparentDrawables.clear();
}

void Renderer::updateScene() {
	if (!rootSceneNode) {
		return;
	}
	updateNode(rootSceneNode, glm::mat4(1.0f));

	
}



void Renderer::postRender()
{
	opaqueDrawables.clear();
	transparentDrawables.clear();
	lights.clear();
}

void Renderer::updateNode(SceneNode* node, const glm::mat4& CTM) {
	node->updateWorldTransform(CTM);

	if (DrawNode* drawNode = dynamic_cast<DrawNode*>(node)) {
		if (drawNode->isTransparent()) {
			glm::vec3 nodePosition = glm::vec3(node->getWorldTransform()[3]);
			float distance = glm::length(mainCamera->Position - nodePosition);
			transparentDrawables[distance] = drawNode;//adding to map container using distance as key automatically does the sorting
		}
		else {
			opaqueDrawables.push_front(drawNode);
		}
	}

	else if (LightNode* lightNode = dynamic_cast<LightNode*>(node)) {
		if (lights.size() > MAX_LIGHTS) {
			std::cout << "Reached maximum of "<< MAX_LIGHTS <<" lights, can't add more!" << std::endl;
			return;
		}
		lights.push_back(lightNode);
	}

	else if (GroupNode* groupNode = dynamic_cast<GroupNode*>(node)) {
		for (auto& child : groupNode->getChildren()) {
			updateNode(child, node->getWorldTransform());
		}
	}
}

void Renderer::renderNode(DrawNode* node) {
	Material material = node->getMaterial();
	glm::mat4 model = node->getWorldTransform();
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
	if (GLuint texture = node->getTexture()) {
		blendingShader->use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		blendingShader->setMat4("model", model);
		blendingShader->setMat3("normalMatrix", normalMatrix);

		blendingShader->setVec3("material.ambient", material.ambient);
		blendingShader->setVec3("material.diffuse", material.diffuse);
		blendingShader->setVec3("material.specular", material.specular);
		blendingShader->setFloat("material.shininess", material.shininess);

	}
	else {
		genericShader->use();
		genericShader->setMat4("model", model);
		genericShader->setMat3("normalMatrix", normalMatrix);

		genericShader->setVec3("material.ambient", material.ambient);
		genericShader->setVec3("material.diffuse", material.diffuse);
		genericShader->setVec3("material.specular", material.specular);
		genericShader->setFloat("material.shininess", material.shininess);
	}
	node->draw();
}

void Renderer::shadowRenderNode(DrawNode* node) {
	shadowShader->setMat4("model", node->getWorldTransform());
	node->draw();
}
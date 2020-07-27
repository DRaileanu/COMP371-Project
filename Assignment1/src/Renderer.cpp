#include "Renderer.h"


Renderer::Renderer(Camera* camera, Shader* genericShader,  Shader* lightingMaterial, Shader* lightingTexture, Shader* shadowShader) {
	this->mainCamera = camera;
	this->genericShader = genericShader;
	this->lightingMaterial = lightingMaterial;
	this->lightingTexture = lightingTexture;
	this->shadowShader = shadowShader;
	shadowCasterLight = NULL;

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
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);

	lightingMaterial->use();
	lightingMaterial->setInt("depthCubeMap", 7);
	lightingMaterial->setFloat("far_plane", far_plane);//NOTE: if want to vary far_plane, needs to be inside render(). Putting here to reduce setting uniforms

	lightingTexture->use();
	lightingTexture->setInt("texture1", 0);
	lightingTexture->setInt("depthCubeMap", 7);
	lightingTexture->setFloat("far_plane", far_plane);




	GLuint materialIndex = glGetUniformBlockIndex(lightingMaterial->ID, "PointLights");
	glUniformBlockBinding(lightingMaterial->ID, materialIndex, 0);

	GLuint textureIndex = glGetUniformBlockIndex(lightingTexture->ID, "PointLights");
	glUniformBlockBinding(lightingTexture->ID, textureIndex, 0);

	glGenBuffers(1, &pointLightsUniformBlock);
	glBindBuffer(GL_UNIFORM_BUFFER, pointLightsUniformBlock);
	glBufferData(GL_UNIFORM_BUFFER, 64 * MAX_LIGHTS, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);


	glBindBufferBase(GL_UNIFORM_BUFFER, 0, pointLightsUniformBlock);


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


	//NOTE: checking only for shadowCasterLight can result in case where light was set but was removed from Scene Graph
	//solution: std::find to see if its inside lights vector. Leaving like this for now since curious what sort of bugs can I get
	if (shadowMode && shadowCasterLight) {

		//TODO for now only PointLight implementation of shadows is made. Add others if needed later
		if (shadowCasterLight->getType() == LightType::PointLight) {
			glm::vec3 lightPos = shadowCasterLight->getWorldTransform()[3];//light position relative to which shadows are created
			//create depthCubeMap transformation matrics
			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
			std::vector<glm::mat4> shadowTransforms;
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

			//render scene to depthCubeMap
			//----------------------------
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);//switch viewport since depthMap might use different resolution (SHADOW_WIDTH * SHADOW_HEIGHT)
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);//bind and clear depthMap frame buffer
			glClear(GL_DEPTH_BUFFER_BIT);
			//configure shadowShader
			shadowShader->use();
			for (unsigned int i = 0; i < 6; ++i) {
				shadowShader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
			}
			shadowShader->setFloat("far_plane", far_plane);//needed to clamp distance from Frag_Depth and lightPos to [0,1] in shadow.fs
			shadowShader->setVec3("lightPos", lightPos);

			//render scene into depthCubeMap
			glEnable(GL_CULL_FACE);
			for (auto& node : opaqueTexDraws) {
				shadowRenderNode(node);
			}
			for (auto& node : opaqueMaterialDraws) {
				shadowRenderNode(node);
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);//for safety
			glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

			//provide shaders that implement shadows position of shadowCastingLight
			lightingMaterial->use();
			lightingMaterial->setVec3("shadowCastingLightPos", lightPos);
			lightingTexture->use();
			lightingTexture->setVec3("shadowCastingLightPos", lightPos);
		}
		//TODO if DirLight & if SpotLight

	}





	//configure rest of shaders
	//---------------------

	glBindBuffer(GL_UNIFORM_BUFFER, pointLightsUniformBlock);
	for (int i = 0; i < lights.size(); ++i) {
		LightProperties prop = lights[i]->getProperties();
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 4 * i, sizeof(glm::vec3), &lights[i]->getWorldTransform()[3]);
		for (int j = 0; j < 3; ++j) {
			glBufferSubData(GL_UNIFORM_BUFFER, (sizeof(glm::vec4) * 4 * i) + (sizeof(glm::vec4) * (j + 1)), sizeof(glm::vec3), &prop.ambient + j);
		}
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);



	genericShader->use();
	genericShader->setMat4("VP", VP);


	lightingMaterial->use();
	lightingMaterial->setMat4("VP", VP);
	lightingMaterial->setVec3("viewPos", viewPos);
	lightingMaterial->setBool("shadows", shadowMode);



	lightingTexture->use();
	lightingTexture->setMat4("VP", VP);
	lightingTexture->setVec3("viewPos", viewPos);
	lightingTexture->setBool("shadows", shadowMode);






	//std::sort(opaqueTexDraws.begin(), opaqueTexDraws.end(), [](DrawNode* a, DrawNode* b) {return a->getTexture() < b->getTexture(); });

	


	
	// render opaques before transparents
	glDisable(GL_BLEND);//needs to be disabled just in case Drawable has alpha <1.0 but DrawNode sets transparency to false
	glEnable(GL_CULL_FACE);//optimization


	genericShader->use();
	for (auto& node : genericDraws) {
		renderNode(node, genericShader);
	}
	lightingTexture->use();
	lightingTexture->setFloat("texRatio", texRatio);
	for (auto& node : opaqueTexDraws) {
		glActiveTexture(GL_TEXTURE0); 
		glBindTexture(GL_TEXTURE_2D, node->getTexture());
		renderNode(node, lightingTexture);
	}
	lightingMaterial->use();
	for (auto& node : opaqueMaterialDraws) {
		renderNode(node, lightingMaterial);
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
	genericShader->use();
	glCullFace(GL_FRONT);
	for (auto iter = transparentDraws.rbegin(); iter != transparentDraws.rend(); ++iter) {
		genericShader->setFloat("transparency", iter->second->getTransparency());
		renderNode(iter->second, genericShader);
	}
	glCullFace(GL_BACK);
	for (auto iter = transparentDraws.rbegin(); iter != transparentDraws.rend(); ++iter) {
		genericShader->setFloat("transparency", iter->second->getTransparency());
		renderNode(iter->second, genericShader);
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
	genericDraws.clear();
	opaqueTexDraws.clear();
	opaqueMaterialDraws.clear();
	transparentDraws.clear();
	lights.clear();
}

// update SceneGraph and collect DrawNodes to be rendered
// TODO instead of dynamic_cast, implement visitor pattern
void Renderer::updateNode(SceneNode* node, const glm::mat4& CTM) {
	node->updateWorldTransform(CTM);

	if (DrawNode* drawNode = dynamic_cast<DrawNode*>(node)) {
		if (drawNode->getTransparency() > 0) {
			glm::vec3 nodePosition = glm::vec3(node->getWorldTransform()[3]);
			float distance = glm::length(mainCamera->Position - nodePosition);
			transparentDraws[distance] = drawNode;//adding to map container using distance as key automatically does the sorting from closest to furthest away
		}
		else if (drawNode->getMaterial()) {
			if (drawNode->getTexture()) {
				opaqueTexDraws.push_back(drawNode);
			}
			else {
				opaqueMaterialDraws.push_back(drawNode);
			}
		}
		else { genericDraws.push_back(drawNode); }
	}

	else if (LightNode* lightNode = dynamic_cast<LightNode*>(node)) {
		if (lights.size() > MAX_LIGHTS) {
			std::cout << "Reached maximum of " << MAX_LIGHTS << " lights, can't add more!" << std::endl;
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

void Renderer::renderNode(DrawNode* node, Shader* shader) {

	glm::mat4 model = node->getWorldTransform();
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));


	shader->setMat4("model", model);
	shader->setMat3("normalMatrix", normalMatrix);

	if (shader == lightingMaterial || shader == lightingTexture) {
		Material* material = node->getMaterial();
		shader->setVec3("material.ambient", material->ambient);
		shader->setVec3("material.diffuse", material->diffuse);
		shader->setVec3("material.specular", material->specular);
		shader->setFloat("material.shininess", material->shininess);
	}
	

	node->draw();
}

// render nodes to depthMap
void Renderer::shadowRenderNode(DrawNode* node) {
	shadowShader->setMat4("model", node->getWorldTransform());
	node->draw();
}
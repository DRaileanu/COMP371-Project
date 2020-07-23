#include "Renderer.h"


Renderer::Renderer(Camera* camera, Shader* genericShader, Shader* blendingShader) {
	this->mainCamera = camera;
	this->genericShader = genericShader;
	this->blendingShader = blendingShader;

	polygonMode = GL_TRIANGLES;
	texRatio = 1.0f;




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

	glm::mat4 projection = glm::perspective(glm::radians(mainCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
	glm::mat4 view = mainCamera->GetViewMatrix();

	genericShader->use();
	genericShader->setMat4("projection", projection);
	genericShader->setMat4("view", view);

	blendingShader->use();
	blendingShader->setMat4("projection", projection);
	blendingShader->setMat4("view", view);


	// render opaques first
	glDisable(GL_BLEND);//does it really need to be disabled?
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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
	rootSceneNode->updateWorldTransform(glm::mat4(1.0f));
	updateNode(rootSceneNode, rootSceneNode->getWorldTransform());

	
}



void Renderer::postRender()
{
	opaqueDrawables.clear();
	transparentDrawables.clear();
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

	else if (GroupNode* groupNode = dynamic_cast<GroupNode*>(node)) {
		for (auto& child : groupNode->getChildren()) {
			updateNode(child, node->getWorldTransform());
		}
	}
}

void Renderer::renderNode(DrawNode* node) {
	if (GLuint texture = node->getTexture()) {
		blendingShader->use();
		blendingShader->setInt("texture1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		blendingShader->setMat4("model", node->getWorldTransform());

		node->draw();
	}
	else {
		genericShader->use();
		genericShader->setMat4("model", node->getWorldTransform());
		node->draw();
	}
}


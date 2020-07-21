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

	preRender(rootSceneNode);

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

	glDisable(GL_BLEND);

	for (auto& node : opaqueDrawables) {
		renderNode(node);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto& node : transparentDrawables) {
		renderNode(node.second);
	}

	opaqueDrawables.clear();
	transparentDrawables.clear();

}

void Renderer::preRender(SceneNode* node) {
	if (!node) {
		return;
	}

	node->updateWorldTransform();

	if (Drawable* nodeDrawable= node->getDrawable()) {
		if (nodeDrawable->isTransparent()) {//if transparent, sort form front to back
			float distance = glm::length(mainCamera->Position - glm::vec3(node->getWorldTransform()[4]));//so ugly! make nicer if got time
			transparentDrawables[distance] = node;//adding to map container using distance as key automatically does the sorting
		}
		else {
			opaqueDrawables.push_front(node);
		}
	}

	for (auto& child : node->getChildren()) {
		preRender(child);
	}
}


void Renderer::setRootSceneNode(SceneNode* node) {
	rootSceneNode = node;
}

void Renderer::removeRootSceneNode(SceneNode* node) {
	rootSceneNode = NULL;
}


void Renderer::renderNode(SceneNode* node) {
	if (node->getDrawable()->getTexture()) {
		blendingShader->use();
		blendingShader->setInt("texture1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, node->getDrawable()->getTexture());
		blendingShader->setMat4("model", node->getWorldTransform());

		node->draw();
	}
	else {
		genericShader->use();
		genericShader->setMat4("model", node->getWorldTransform());
		node->draw();
	}
}


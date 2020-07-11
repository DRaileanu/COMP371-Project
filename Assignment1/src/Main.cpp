#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "SceneNode.h"
#include "Model.h"
#include "Grid.h"
#include "AxisLines.h"

#include <iostream>

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

GLFWwindow* window;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------

void programInit();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

//eventually goes into Renderer class
void drawNode(SceneNode*, Shader*);



//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------
int main() {
    //initialize OpenGL libraries and create window
    programInit();

    // build and compile shader program
    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // set up the Scene Graph (automatically sets up vertex data, buffers and configures vertex attributes)
    // ------------------------------------------------------------------  
    
    //root, grid and axis lines
    SceneNode* root = new SceneNode;
    root->scale(glm::vec3(0.25, 0.25, 0.25));

    SceneNode* axisLines = new SceneNode(new AxisLines);
    axisLines->scale(glm::vec3(10.0f, 10.0f, 10.0f));
    root->addChild(axisLines);

    SceneNode* grid= new SceneNode(new Grid);
    root->addChild(grid);

    //modelsNode to be able to manipulate all models at once
    SceneNode* modelsNode = new SceneNode;
    grid->addChild(modelsNode);


    SceneNode* dan = new SceneNode;
    dan->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    dan->translate(glm::vec3(-40.0f, 0.0f, -40.0f));
    modelsNode->addChild(dan);

    Model* model1 = new Model('N');
    model1->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    dan->addChild(model1);

    Model* model2 = new Model('1');
    model2->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    dan->addChild(model2);


    SceneNode* Moh = new SceneNode;
    Moh->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    Moh->translate(glm::vec3(40.0f, 0.0f, -40.0f));
    modelsNode->addChild(Moh);

    Model* model3 = new Model('H');
    model3->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    Moh->addChild(model3);

    Model* model4 = new Model('5');
    model4->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    Moh->addChild(model4);

    
    SceneNode* muher = new SceneNode;
    muher->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    muher->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
    muher->translate(glm::vec3(-40.5f, 0.0f, 40.5f));
    modelsNode->addChild(muher);

    Model* model5 = new Model('H');
    model5->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    muher->addChild(model5);

    Model* model6 = new Model('2');
    model6->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    muher->addChild(model6);


    SceneNode* radhep = new SceneNode;
    radhep->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    radhep->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
    radhep->translate(glm::vec3(40.0f, 0.0f, 40.0f));
    modelsNode->addChild(radhep);

    Model* model7 = new Model('D');
    model7->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    radhep->addChild(model7);

    Model* model8 = new Model('3');
    model8->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    radhep->addChild(model8);


    SceneNode* mohd = new SceneNode;
    mohd->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    mohd->translate(glm::vec3(0.0f, 0.0f, -5.0f));
    modelsNode->addChild(mohd);

    Model* model9 = new Model('H');
    model9->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    mohd->addChild(model9);

    Model* model10 = new Model('1');
    model10->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    mohd->addChild(model10);
    
    
    // load and create a texture 
    // -------------------------
    



    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            dan->scale(glm::vec3(1.01f, 1.01f, 1.01f));
            Moh->scale(glm::vec3(1.01f, 1.01f, 1.01f));
            muher->scale(glm::vec3(1.01f, 1.01f, 1.01f));
            radhep->scale(glm::vec3(1.01f, 1.01f, 1.01f));
            mohd->scale(glm::vec3(1.01f, 1.01f, 1.01f));
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            dan->scale(glm::vec3(0.99f, 0.99f, 0.99f));
            Moh->scale(glm::vec3(0.99f, 0.99f, 0.99f));
            muher->scale(glm::vec3(0.99f, 0.99f, 0.99f));
            radhep->scale(glm::vec3(0.99f, 0.99f, 0.99f));
            mohd->scale(glm::vec3(0.99f, 0.99f, 0.99f));
        }


        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
       

        // activate shader
        shader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader.setMat4("projection", projection); //use whatever shader we want

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);



        // render objects
        //dan->rotate(glm::vec3(0.0f, 3.0f, 0.0f));
        //Moh->rotate(glm::vec3(0.0f, 3.0f, 0.0f));
        //muher->rotate(glm::vec3(0.0f, 3.0f, 0.0f));
        //radhep->rotate(glm::vec3(0.0f, 3.0f, 0.0f));
        //mohd->rotate(glm::vec3(0.0f, 3.0f, 0.0f));

        root->updateWorldTransform(currentFrame);
        drawNode(root, &shader);

        //glm::mat4 model;
        //model = glm::mat4(1.0f);
        //shader.setMat4("model", model);
        //cube.draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


// initialize glfw and create window, then use glad to load function pointers
// TODO abstract into window class
// --------------------------------------------------------------------------
void programInit() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    // set required callback functions
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    //enable z-buffering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //press 1/2 for Wireframe/Fill mode
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}


void drawNode(SceneNode* node, Shader* shader) {
    if (node->getDrawable()) {
        glm::mat4 transform = node->getWorldTransform();
        shader->setMat4("model", transform);
        node->draw();
    }

    for (auto child : node->getChildren()) {
        drawNode(child, shader);
    }
}
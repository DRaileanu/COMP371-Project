#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "SceneNode.h"
#include "Model.h"
#include "Grid.h"
#include "AxisLines.h"

#include <iostream>
#include <algorithm>

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

GLFWwindow* window;


//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------

void programInit();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//TODO move eventually into Renderer class
void drawNode(SceneNode*, Shader*);


//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------
int main() {
    //initialize OpenGL libraries and create window
    programInit();


    //Camera parameters for view transform
    glm::vec3   cameraPosition(0.0f, 0.0f, 20.0f);
    glm::vec3   cameraFront(0.0f, 0.0f, -1.0f);
    glm::vec3   cameraUp(0.0f, 1.0f, 0.0f);
    //other Camera parameters
    float cameraYaw = -90.0f;
    float cameraPitch = 0.0f;
    float cameraSpeed = 10.0f;
    float cameraSensitivity = 5.0f;
    float cameraZoom = 45.0f;

    //frame time parameters
    float lastFrame = glfwGetTime();
    double lastMouseX;
    double lastMouseY;
    glfwGetCursorPos(window, &lastMouseX, &lastMouseY);

    // build and compile shader program
    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");


    // set up the Scene Graph (sets up vertex data, buffers and configures vertex attributes)
    // --------------------------------------------------------------------------------------
    
    //root, grid and axis lines
    SceneNode* root = new SceneNode;
    root->scale(glm::vec3(0.25, 0.25, 0.25));

    SceneNode* axisLines = new SceneNode(new AxisLines);
    axisLines->scale(glm::vec3(10.0f, 10.0f, 10.0f));
    root->addChild(axisLines);

    SceneNode* grid= new SceneNode(new Grid);
    root->addChild(grid);

    // student models
    SceneNode* dan = new SceneNode;
    dan->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    dan->translate(glm::vec3(-40.0f, 0.0f, -40.0f));
    grid->addChild(dan);

    Model* model1 = new Model('N');
    model1->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    dan->addChild(model1);

    Model* model2 = new Model('1');
    model2->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    dan->addChild(model2);


    SceneNode* moh = new SceneNode;
    moh->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    moh->translate(glm::vec3(40.0f, 0.0f, -40.0f));
    grid->addChild(moh);

    Model* model3 = new Model('H');
    model3->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    moh->addChild(model3);

    Model* model4 = new Model('5');
    model4->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    moh->addChild(model4);

    
    SceneNode* muher = new SceneNode;
    muher->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    muher->rotate(glm::vec3(0.0f, 180.0f, 0.0f));
    muher->translate(glm::vec3(-40.5f, 0.0f, 40.5f));
    grid->addChild(muher);

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
    grid->addChild(radhep);

    Model* model7 = new Model('D');
    model7->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    radhep->addChild(model7);

    Model* model8 = new Model('3');
    model8->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    radhep->addChild(model8);


    SceneNode* mohd = new SceneNode;
    mohd->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    mohd->translate(glm::vec3(0.0f, 0.0f, -5.0f));
    grid->addChild(mohd);

    Model* model9 = new Model('H');
    model9->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    mohd->addChild(model9);

    Model* model10 = new Model('1');
    model10->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    mohd->addChild(model10);
    
   
    //default selected node to transform
    SceneNode* selectedNode=mohd;

    //world matrix used to change world orientation
    glm::mat4 world(1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float dt = glfwGetTime() - lastFrame;
        lastFrame += dt;

        // update Camera
        //--------------
        // update mouse cursor
        double mouseX, mouseY, dx=0.0, dy=0.0;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        // process cursor movement only if appropriate mouse button is clicked
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            dx = mouseX - lastMouseX;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            dy = lastMouseY - mouseY;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            cameraZoom -= lastMouseY - mouseY;
            //constrain zoom to avoid flipping
            cameraZoom = std::max(1.0f, std::min(120.0f, cameraZoom));
        }
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        // update camera angular angles
        cameraYaw   += dx * cameraSensitivity * dt;
        cameraPitch += dy * cameraSensitivity * dt;
        // constrain pitch angle so screen doesn't get flipped
        cameraPitch = std::max(-89.0f, std::min(89.0f, cameraPitch));
        // update camera parameters for view transform
        cameraFront.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        cameraFront.y = sin(glm::radians(cameraPitch));
        cameraFront.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        glm::vec3 cameraRight = glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
        cameraUp = glm::cross(cameraRight, cameraFront);


        // keyboard input handling
        // --------------
        // exit program
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // change rendering modes
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // select student models to transform
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            selectedNode = dan;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            selectedNode = moh;
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            selectedNode = muher;
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            selectedNode = radhep;
        }
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            selectedNode = mohd;
        }

        // option to select only letter or digit model for transformations
        if (selectedNode == dan) {
            if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
                selectedNode = model1;
            }
            if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
                selectedNode = model2;
            }
        }
        if (selectedNode == moh) {
            if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
                selectedNode = model3;
            }
            if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
                selectedNode = model4;
            }
        }
        if (selectedNode == muher) {
            if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
                selectedNode = model5;
            }
            if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
                selectedNode = model6;
            }
        }
        if (selectedNode == radhep) {
            if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
                selectedNode = model7;
            }
            if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
                selectedNode = model8;
            }
        }
        if (selectedNode == mohd) {
            if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
                selectedNode = model9;
            }
            if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
                selectedNode = model10;
            }
        }

        // apply transformations
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            selectedNode->scale(glm::vec3(0.5 * dt + 1, 0.5 * dt + 1, 0.5 * dt + 1));
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            selectedNode->scale(glm::vec3(1 - 0.5 * dt, 1 - 0.5 * dt, 1 - 0.5 * dt));
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(-5 * dt, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(5 * dt, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(0.0f, 5 * dt, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(0.0f, -5 * dt, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            selectedNode->rotate(glm::vec3(0.0f, 5.0f, 0.0f));//would use with rotaton with respect to dt, but assignment said 5 degrees
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            selectedNode->rotate(glm::vec3(0.0f, -5.0f, 0.0f));
        }


        // world orientation transformations
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            world = rotate(world, glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            world = rotate(world, -glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            world = rotate(world, glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            world = rotate(world, -glm::radians(2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
            world = glm::mat4(1.0f);
            //uncomment if also want to reset camera when pressing HOME
            //cameraYaw = -90.0f;
            //cameraPitch = 0.0f;
        }
        // pass world orientation matrix to shader
        shader.setMat4("world", world);


        // render
        // ------
        // reset color and clear Depth Buffer Bit
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        // pass projection matrix to shader
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader.setMat4("projection", projection);

        // pass camera/view transformation to shader
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition+cameraFront, cameraUp);
        shader.setMat4("view", view);


        // update and render Scene Graph
        root->updateWorldTransform();
        drawNode(root, &shader);
        

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
    glCullFace(GL_BACK);
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
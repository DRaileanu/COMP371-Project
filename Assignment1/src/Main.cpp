//---------------------------------------------------------------------------------------
// The program uses a modified skeleton code provided by https://learnopengl.com
// The original skeleton code is available at: https://github.com/JoeyDeVries/LearnOpenGL
//---------------------------------------------------------------------------------------

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TextureLoader.h"
#include "Shader.h"
#include "GroupNode.h"
#include "DrawNode.h"
#include "Model.h"
#include "Grid.h"
#include "AxisLines.h"
#include "Renderer.h"
#include "Camera.h"
#include "Sphere.h"


#include <iostream>
#include <algorithm>


//----------------------------------------
// Globals
//----------------------------------------

extern const unsigned int SCR_WIDTH = 1024;//extern, otherwise extern won't work in other classes to get access to it
extern const unsigned int SCR_HEIGHT = 768;//if create Window class, can move in there and not have this

GLFWwindow* window;

Camera* mainCamera;
double lastX;
double lastY;

//----------------------------------------
// Functions prototypes
//----------------------------------------

void ErrorCallback(int, const char* err_str);
void programInit();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);//consider removing



//----------------------------------------
// MAIN
//----------------------------------------
int main() {
    //initialize OpenGL libraries and create window
    programInit();

    // setup Camera
    mainCamera = new Camera(glm::vec3(0.0f, 7.5f, 7.5f));
    glfwGetCursorPos(window, &lastX, &lastY);

    ////frame time parameters
    float lastFrame = glfwGetTime();

    // build and compile shader program
    Shader genericShader("shaders/generic.vs", "shaders/generic.fs");
    Shader lightingMaterial("shaders/lightingMaterial.vs", "shaders/lightingMaterial.fs");
    Shader lightingTexture("shaders/lightingTexture.vs", "shaders/lightingTexture.fs");
    Shader shadowShader("shaders/shadow.vs", "shaders/shadow.fs", "shaders/shadow.gs");

    // setup Renderer
    Renderer* renderer = new Renderer(mainCamera, &genericShader, &lightingMaterial, &lightingTexture, &shadowShader);

    // set up the Scene Graph (sets up vertex data, buffers and configures vertex attributes)
    // --------------------------------------------------------------------------------------

    //root, grid and axis lines
    GroupNode* root = new GroupNode;
    //root->scale(glm::vec3(0.25, 0.25, 0.25));

    DrawNode* axisLines = new DrawNode(new AxisLines);
    axisLines->translate(glm::vec3(0.0f, 0.01, 0.0f));
    axisLines->scale(glm::vec3(10.0f, 10.0f, 10.0f));
    root->addChild(axisLines);

    
    DrawNode* grid = new DrawNode(new Grid);
    Material* gridMaterial = new Material{ glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.75, 0.75f, 0.75f), 32.0 };
    grid->setMaterial(gridMaterial);
    grid->setTexture(loadTexture("res/tile_diffuse.jpg"));
    root->addChild(grid);

    // student models
    GroupNode* dan = new GroupNode;
    dan->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    dan->translate(glm::vec3(-40.0f, 0.0f, -40.0f));
    root->addChild(dan);

    Model* model1 = new Model('N');
    model1->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    dan->addChild(model1);

    Model* model2 = new Model('1');
    model2->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    dan->addChild(model2);


    GroupNode* moh = new GroupNode;
    moh->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    moh->translate(glm::vec3(40.0f, 0.0f, -40.0f));
    root->addChild(moh);

    Model* model3 = new Model('H');
    model3->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    moh->addChild(model3);

    Model* model4 = new Model('5');
    model4->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    moh->addChild(model4);


    GroupNode* muher = new GroupNode;
    muher->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    muher->translate(glm::vec3(-40.0f, 0.0f, 40.0f));
    root->addChild(muher);

    Model* model5 = new Model('H');
    model5->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    muher->addChild(model5);

    Model* model6 = new Model('2');
    model6->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    muher->addChild(model6);


    GroupNode* radhep = new GroupNode;
    radhep->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    radhep->translate(glm::vec3(40.0f, 0.0f, 40.0f));
    root->addChild(radhep);

    Model* model7 = new Model('D');
    model7->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    radhep->addChild(model7);

    Model* model8 = new Model('3');
    model8->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    radhep->addChild(model8);


    GroupNode* mohd = new GroupNode;
    mohd->scale(glm::vec3(2.0f, 2.0f, 2.0f));
    mohd->translate(glm::vec3(0.0f, 0.0f, -5.0f));
    root->addChild(mohd);

    Model* model9 = new Model('H');
    model9->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    mohd->addChild(model9);

    Model* model10 = new Model('1');
    model10->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    mohd->addChild(model10);


    Sphere* spheredraw = new Sphere(5, 6);
    //spheredraw->setColours(glm::vec3(1.0, 0.5f, 0.0f));
    DrawNode* sphere = new DrawNode(spheredraw);
    sphere->translate(glm::vec3(0.0f, 10.0f, -10.0f));
    root->addChild(sphere);
    sphere->setTransparency(0.5f);
    //sphere->setTexture(loadTexture("res/container2.jpg"));


    ////default selected node to transform

    GroupNode* lightNodes = new GroupNode();
    lightNodes->translate(glm::vec3(0.0f, 10.0f, 0.0f));
    root->addChild(lightNodes);

    GroupNode* light1Node = new GroupNode();
    light1Node->translate(glm::vec3(2.0f, 0.0f, 0.0f));
    lightNodes->addChild(light1Node);

    GroupNode* light2Node = new GroupNode();
    light2Node->translate(glm::vec3(-2.0f, 0.0f, 0.0f));
    lightNodes->addChild(light2Node);

    //GroupNode* light3Node = new GroupNode();
    //light3Node->translate(glm::vec3(-1.0f, 0.0f, -3.46f));
    ////lightNodes->addChild(light3Node);

    LightNode* light1 = new LightNode(LightType::PointLight);
    light1->setProperties(LightProperties{
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(2.0f, 2.0f, 2.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        });
    light1Node->addChild(light1);

    LightNode* light2 = new LightNode(LightType::PointLight);
    light2->setProperties(LightProperties{
        glm::vec3(0.25f, 0.25f, 0.25f),
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        });
    //light2Node->addChild(light2);

    //LightNode* light3 = new LightNode(LightType::PointLight);
    //light3->setProperties(LightProperties{
    //    glm::vec3(0.25f, 0.25f, 0.25f),
    //    glm::vec3(1.0f, 1.0f, 1.0f),
    //    glm::vec3(1.0f, 1.0f, 1.0f)
    //    });
    //light3Node->addChild(light3);

    Drawable* lightcube = new Cube;
    lightcube->setColours(glm::vec3(1.0f));
    DrawNode* light1cube = new DrawNode(lightcube);
    light1cube->translate(glm::vec3(0.0f, 0.0f, 0.5f));
    light1Node->addChild(light1cube);

    DrawNode* light2cube = new DrawNode(lightcube);
    light2cube->translate(glm::vec3(0.0f, 0.0f, 0.5f));
    light2Node->addChild(light2cube);

    //DrawNode* light3cube = new DrawNode(lightcube);
    //light3cube->translate(glm::vec3(0.0f, 0.75f, 0.0f));
    //light3Node->addChild(light3cube);

    //world matrix used to change world orientation
    glm::mat4 world(1.0f);


    SceneNode* selectedNode = lightNodes;

    renderer->setShadowCasterLight(light1);
    
    renderer->setRootSceneNode(root);

    //------------------------------------------------------------------------------

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // update frame time parameters
        float dt = glfwGetTime() - lastFrame;
        lastFrame += dt;

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
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
            selectedNode->translate(glm::vec3(0.0f, 0.0f, -5 * dt));//confirmed with teacher that UP/DOWN meant along z-axis
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
            selectedNode->translate(glm::vec3(0.0f, 0.0f, 5 * dt));
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(0.0f, 5 * dt, 0.0f));//confirmed with teacher that UP/DOWN meant along z-axis
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(0.0f, -5 * dt, 0.0f));
        }


        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            selectedNode->rotate(glm::vec3(0.0f, 5.0f, 0.0f));//would use with rotaton with respect to dt, but assignment said 5 degrees
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            selectedNode->rotate(glm::vec3(0.0f, -5.0f, 0.0f));
        }



        // world orientation transformations
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            mainCamera->ProcessKeyboard(BACKWARD, dt);
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            mainCamera->ProcessKeyboard(FORWARD, dt);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            mainCamera->ProcessKeyboard(LEFT, dt);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            mainCamera->ProcessKeyboard(RIGHT, dt);
        }

        //// world orientation transformations
        //if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        //    root->rotate(glm::vec3(1.0f, 0.0f, 0.0f));
        //}
        //if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        //    root->rotate(glm::vec3(-1.0f, 0.0f, 0.0f));
        //}
        //if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        //    root->rotate(glm::vec3(0.0f, 1.0f, 0.0f));
        //}
        //if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        //    root->rotate(glm::vec3(0.0f, -1.0f, 0.0f));
        //}
        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
            root->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
            //comment next 2 lines if don't want camera to reset looking at towards -z axis
            mainCamera->Yaw = -90.0f;
            mainCamera->Pitch = 0.0f;
        }


        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
            renderer->setShadowMode(false);
        }
        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
            renderer->setShadowMode(true);
        }



        // render
        // ------
        renderer->updateScene();
        //for (int i = 0; i < 100; ++i) {//for benchmarking performance by updateScene/render many times
        //   
        //}
        renderer->render();
        renderer->postRender();

        static int frames = 1;
        static float total = 0;
        total += 1/dt;
        float avg = total / frames;
        frames++;
        std::cout << '\r' << "dt: " << dt << "\tFPS: " << 1 / dt << "\tavgFPS: " << avg;;//for debugging

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




//----------------------------------------
// Function definitions
//----------------------------------------

// for debugging if getting error
void ErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}

// initialize glfw and create window, then use glad to load function pointers
// TODO abstract into window class
// --------------------------------------------------------------------------
void programInit() {
    // glfw: initialize and configure
    glfwSetErrorCallback(ErrorCallback);
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
    //glfwSetKeyCallback(window, key_callback);//remove if deleting key_callback()

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


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    mainCamera->ProcessMouseMovement(xoffset, yoffset);
}

//consider removing, since most keys control variables from main
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}
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


#include "shader.h"
#include "SceneNode.h"
#include "Model.h"
#include "Grid.h"
#include "AxisLines.h"
#include "BuildingCube.h"

#include <iostream>
#include <algorithm>
#include <queue>


//----------------------------------------
// Globals
//----------------------------------------

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

GLFWwindow* window;


//----------------------------------------
// Functions prototypes
//----------------------------------------

void programInit();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//TODO move eventually into Renderer class
void drawNode(SceneNode*, Shader*);


//----------------------------------------
// MAIN
//----------------------------------------
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
    float cameraSensitivity = 5.0f;
    float cameraZoom = 45.0f;

    //frame time parameters
    float lastFrame = glfwGetTime();
    double lastMouseX;
    double lastMouseY;
    glfwGetCursorPos(window, &lastMouseX, &lastMouseY);

    // build and compile shader program
    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Shader buildShader("shaders/build_vertex_shader.glsl", "shaders/build_fragment_shader.glsl");//need another shader that uses uniforms to set colour, so we can change BuildingCube colours before placement


    // set up the Scene Graph (sets up vertex data, buffers and configures vertex attributes)
    // --------------------------------------------------------------------------------------

    //root, grid and axis lines
    SceneNode* root = new SceneNode;

    SceneNode* axisLines = new SceneNode(new AxisLines);
    axisLines->scale(glm::vec3(3.0f, 3.0f, 3.0f));
    root->addChild(axisLines);

    SceneNode* grid = new SceneNode(new Grid);;
    grid->translate(glm::vec3(0.0f, -0.0001f, 0.0f));
    root->addChild(grid);

    
    //ameModels is parent of all Letter Models
    //I'm using an additional SceneNode for every Letter Model because the Models are centered around x=y=z=0 in order to allow rotation around their center.
    //Translating the Letter Model directly above xz plane will work at first, but then when it's scaled, the bottom would go below xz plane. The extra SceneNode allows me to scale and stay on xz plane.
    //So we rotate using letter models and scale/translate using letterNode. Translating twice in between rotations won't work with current implementation of SceneNode

    SceneNode* nameModels = new SceneNode;
    nameModels->translate(glm::vec3(0.0f, 0.0f, -49.0f));//move all letters at the back
    grid->addChild(nameModels);


    SceneNode* letter1Node = new SceneNode;
    letter1Node->translate(glm::vec3(-15.0f, 0.0f, 0.0f));
    nameModels->addChild(letter1Node);
    Model* letter1 = new Model('R', glm::vec3(1.0f, 0.0f, 0.0f));
    letter1->translate(glm::vec3(0.0f, 2.15f, 0.0f));
    letter1Node->addChild(letter1);

    
    SceneNode* letter2Node = new SceneNode;
    letter2Node->translate(glm::vec3(-9.0f, 0.0f, 0.0f));
    nameModels->addChild(letter2Node);
    Model* letter2 = new Model('A', glm::vec3(1.0f, 0.5f, 0.0f));
    letter2->translate(glm::vec3(0.0f, 2.15f, 0.0f));
    letter2Node->addChild(letter2);


    SceneNode* letter3Node = new SceneNode;
    letter3Node->translate(glm::vec3(-3.0f, 0.0f, 0.0f));
    nameModels->addChild(letter3Node);
    Model* letter3 = new Model('I', glm::vec3(0.0f, 1.0f, 1.0f));
    letter3->translate(glm::vec3(0.0f, 2.15f, 0.0f));
    letter3Node->addChild(letter3);


    SceneNode* letter4Node = new SceneNode;
    letter4Node->translate(glm::vec3(3.0f, 0.0f, 0.0f));
    nameModels->addChild(letter4Node);
    Model* letter4 = new Model('L', glm::vec3(0.5f, 0.0f, 1.0f));
    letter4->translate(glm::vec3(0.0f, 2.15f, 0.0f));
    letter4Node->addChild(letter4);


    SceneNode* letter5Node = new SceneNode;
    letter5Node->translate(glm::vec3(9.0f, 0.0f, 0.0f));
    nameModels->addChild(letter5Node);
    Model* letter5 = new Model('E', glm::vec3(1.0f, 0.0f, 1.0f));
    letter5->translate(glm::vec3(0.0f, 2.15f, 0.0f));
    letter5Node->addChild(letter5);


    SceneNode* letter6Node = new SceneNode;
    letter6Node->translate(glm::vec3(15.0f, 0.0f, 0.0f));
    nameModels->addChild(letter6Node);
    Model* letter6 = new Model('A', glm::vec3(0.0f, 0.5f, 1.0f));
    letter6->translate(glm::vec3(0.0f, 2.15f, 0.0f));
    letter6Node->addChild(letter6);
    

    // default selected node to transform
    // need 2 nodes, since rotations need to be applied on Letter Model, while translation and scaling have to be applied on the SceneNode containing the Letter Model
    SceneNode* selectedNode = nameModels;
    SceneNode* selectedLetter = nameModels;

 

    //EXTRA: Building Mode
    //--------------------
    //need another root for building since needs to be rendered using a different shader
    bool buildingMode = false;
    SceneNode* buildRoot = new SceneNode;
    SceneNode* buildModel = NULL;//gets defined when first cube is placed and becomes center of rotation
    SceneNode* buildCube = new SceneNode(new BuildingCube);//visual to see where we can place new cube
    buildRoot->addChild(buildCube);
    bool placementKeyPressed = false;//used to avoid new cubes to be placed at every frame when pressing placement key

    std::queue<glm::vec3> buildColors;//available colors of cubes we can place. Using it as a circular queue
    buildColors.push(glm::vec3(1.0f, 0.0f, 0.0f));
    buildColors.push(glm::vec3(1.0f, 0.5f, 0.0f));
    buildColors.push(glm::vec3(1.0f, 1.0f, 0.0f));
    buildColors.push(glm::vec3(0.0f, 1.0f, 0.0f));
    buildColors.push(glm::vec3(0.0f, 0.0f, 1.0f));
    buildColors.push(glm::vec3(1.0f, 0.0f, 1.0f));
    glm::vec3 currentBuildColor = buildColors.front();
    bool colorSwitchKeyPressed = false;//so colors only change on initial key press


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
        double mouseX, mouseY, dx, dy;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        dx = mouseX - lastMouseX;
        dy = lastMouseY - mouseY;
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        // update camera angular angles only if appropriate button is pressed
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            cameraYaw += dx * cameraSensitivity * dt;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            cameraPitch += dy * cameraSensitivity * dt;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            cameraZoom -= dy;
            //constrain zoom to avoid flipping
            cameraZoom = std::max(1.0f, std::min(120.0f, cameraZoom));
        }
        // constrain pitch angle so screen doesn't get flipped
        cameraPitch = std::max(-89.0f, std::min(89.0f, cameraPitch));
        // update camera parameters for view transform
        cameraFront.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        cameraFront.y = sin(glm::radians(cameraPitch));
        cameraFront.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        cameraFront = glm::normalize(cameraFront);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));



        // keyboard input handling
        // --------------
        // Camera movement
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
            cameraPosition -= 10 * dt * cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
            cameraPosition += 10 * dt * cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
            cameraPosition -= 10 * dt * cameraRight;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
            cameraPosition += 10 * dt * cameraRight;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
            cameraPosition += 10 * dt * cameraUp;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE) {
            cameraPosition -= 10 * dt * cameraUp;
        }


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


        // select model to transform
        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
            selectedNode = nameModels;
            selectedLetter = nameModels;
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            selectedNode = letter1Node;
            selectedLetter = letter1;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            selectedNode = letter2Node;
            selectedLetter = letter2;
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            selectedNode = letter3Node;
            selectedLetter = letter3;
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            selectedNode = letter4Node;
            selectedLetter = letter4;
        }
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            selectedNode = letter5Node;
            selectedLetter = letter5;
        }
        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
            selectedNode = letter6Node;
            selectedLetter = letter6;

        }
        if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
            if (buildModel) {
                selectedNode = buildModel;
                selectedLetter = buildModel;
            }
        }
        


        // apply model transformations
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
            selectedNode->translate(glm::vec3(0.0f, 0.0f, -5 * dt));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(0.0f, 0.0f, 5 * dt));
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(0.0f, 5*dt, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            selectedNode->translate(glm::vec3(0.0f, -5*dt, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            selectedLetter->rotate(glm::vec3(0.0f, 50*dt, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            selectedLetter->rotate(glm::vec3(0.0f, -50*dt, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
            selectedLetter->rotate(glm::vec3(0.0f, 0.0f, 50*dt));
        }
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            selectedLetter->rotate(glm::vec3(0.0f, 0.0f, -50*dt));
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            selectedLetter->rotate(glm::vec3(-50*dt, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            selectedLetter->rotate(glm::vec3(50*dt, 0.0f, 0.0f));
        }

        // world orientation
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
            root->rotate(glm::vec3(-50*dt, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
            root->rotate(glm::vec3(50 * dt, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
            root->rotate(glm::vec3(0.0f, -50 * dt, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
            root->rotate(glm::vec3(0.0f, 50 * dt, 0.0f));
        }
        // reset world orientation and camera to original state
        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
            root->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
            cameraPosition = glm::vec3(0.0f, 0.0f, 20.0f);
            cameraYaw = -90.0f;
            cameraPitch = 0.0f;
        }


        // Building Mode control
        //----------------------
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            buildingMode = true;
        }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
            buildingMode = false;
        }
        if (buildingMode) {
            // remove currently built model if it exists
            if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && buildModel != NULL) {
                root->removeChild(buildModel);
                delete buildModel;
                buildModel = NULL;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !placementKeyPressed) {
                // first placed cube becomes root of buildingModel, so all transformations are relative to it
                if (buildModel == NULL) {
                    buildModel = new SceneNode;
                    buildModel->setTranslation(buildCube->getTranslate());
                    root->addChild(buildModel);
                }
                placementKeyPressed = true;
                SceneNode* newNode = new SceneNode(new Cube(currentBuildColor));
                newNode->translate(buildCube->getTranslate() - buildModel->getTranslate());
                buildModel->addChild(newNode);
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && placementKeyPressed) {
                placementKeyPressed = false;
            }
            //switch colors of the next placed cube
            if ((glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) && !colorSwitchKeyPressed) {
                colorSwitchKeyPressed = true;
                buildColors.push(buildColors.front());
                buildColors.pop();
                currentBuildColor = buildColors.front();
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_RELEASE && colorSwitchKeyPressed) {
                colorSwitchKeyPressed = false;
            }
        }

        // render
        // ------
        // reset color and clear Depth Buffer Bit
        glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // activate shader
        shader.use();
        // pass projection and camera/view  transformations to shader
        glm::mat4 projection = glm::perspective(glm::radians(cameraZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader.setMat4("projection", projection);

        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        shader.setMat4("view", view);

       

        // update and render Scene Graph
        shader.use();
        root->updateWorldTransform();
        drawNode(root, &shader);



        // update and render BuildingCube
        if (buildingMode) {
            glm::vec3 buildTranslation = cameraPosition + cameraFront * glm::vec3(5.0f, 5.0f, 5.0f);
            buildCube->setTranslation(buildTranslation);

            buildShader.use();
            buildShader.setMat4("projection", projection);
            buildShader.setMat4("view", view);
            buildShader.setVec3("aColor", currentBuildColor);
            buildRoot->updateWorldTransform();
            drawNode(buildRoot, &buildShader);
        }


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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR);

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

//recursively draws the Scene Graph
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

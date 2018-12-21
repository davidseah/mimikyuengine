#include <glad\glad.h>
#include <GLFW\glfw3.h>

//GLM
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "box.h"
#include "CubeMap.h"

Camera camera(glm::vec3(0.f, 2.0, 10.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//windows size
const int width = 800;
const int height = 600;

// camera

float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, -20.0f);


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Mimikyuengine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader boxShader("../material.vs", "../material.frag");
    Shader lampShader("../lamp.vs", "../lamp.frag");
    Box box;
    Box lamp;


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        //Render
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();

        //Draw Lamp
        lampShader.Use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        glm::mat4 lamptransform;
        lamptransform = glm::translate(lamptransform, lightPos);
        lamptransform = glm::scale(lamptransform, glm::vec3(0.2f));
        lampShader.setMat4("model", lamptransform);
        lamp.Draw();


        //Draw Box
        boxShader.Use();
        boxShader.setVec3("light.position", lightPos);
        boxShader.setVec3("viewPos", camera.Position);

        //light properties
        glm::vec3 lightColor(1.0f, 0.0f, 0.0f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        boxShader.setVec3("light.ambient", ambientColor);
        boxShader.setVec3("light.diffuse", diffuseColor);
        boxShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


        //material properties
        boxShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        boxShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        boxShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        boxShader.setFloat("material.shininess", 32.0f);

        for (int i = 0; i < 3; ++i)
        {
            glm::mat4 boxtransformation;
            boxtransformation = glm::translate(boxtransformation, glm::vec3(0, i * 2, 0)); // translate it down so it's at the center of the scene
            boxtransformation = glm::scale(boxtransformation, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
            boxShader.setMat4("model", boxtransformation);
            boxShader.setMat4("projection", projection);
            boxShader.setMat4("view", view);
            box.Draw();
        }


        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
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

    //camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
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
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


//Model Drawing
#define SUPERMODEL 0
#define LAMP    0
#define BOX     1

std::vector<std::string>faces
{
    "C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\darkskies\\darkskies_rt.tga",
    "C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\darkskies\\darkskies_lf.tga",
    "C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\darkskies\\darkskies_up.tga",
    "C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\darkskies\\darkskies_dn.tga",
    "C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\darkskies\\darkskies_ft.tga",
    "C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\darkskies\\darkskies_bk.tga"
};

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

#ifdef NOTNEEDED
    Shader ourShader("../shader.vs", "../shader.frag");
    Shader lightShader("../lighting.vs", "../lighting.frag");
    Shader lampShader("../lamp.vs", "../lamp.frag");
    Shader skyboxShader("../cubemap.vs", "../cubemap.frag");
#endif
    Shader boxShader("../box.vs", "../box.frag");


    //Model ourModel("c:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\GLTF_MODEL\\duck\\Duck.gltf");
    //Model light("c:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\GLTF_MODEL\\Box\\Box.gltf");
    //Model SuperModel("C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\GLTF_MODEL\\centurion\\centurion.gltf");
#ifdef NOTNEEDED
    Box lamp;
    Box light;
    CubeMap map;
#endif
    Box box;

    //unsigned int cubemapTexture = loadCubemap(faces);

    while (!glfwWindowShouldClose(window))
    {
        //ourShader.Use();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //camera.AxisAngleRotation(glm::vec3(0, 1, 0), deltaTime);

        //camera.Position()
        processInput(window);
        //Render
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float test = glm::radians(camera.Zoom);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();


        //ourShader.setMat4("projection", projection);
        //ourShader.setMat4("view", view);

#ifdef NOTNEEDED
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            lightPos.x += 0.1;
        }

        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        {
            lightPos.x -= 0.1;
        }


        // render the loaded model
        glm::mat4 lampmodel;
        lampmodel = glm::translate(lampmodel, glm::vec3(1, 1, 1)); // translate it down so it's at the center of the scene
        lampmodel = glm::scale(lampmodel, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", lampmodel);
        ourModel.Draw(ourShader);


        glm::mat4 model = glm::mat4();
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        //ourMode2.Draw(ourShader);
#endif

#if SUPERMODEL == 1

        //Draw SuperModel
        //SuperModel.Draw(ourShader);  
#endif

#if LAMP == 1

        //Draw Lamp
        lampShader.Use();
        glm::mat4 lampmodel;
        lampmodel = glm::translate(lampmodel, glm::vec3(1, 1, 1)); // translate it down so it's at the center of the scene
        lampmodel = glm::scale(lampmodel, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        lampShader.setMat4("model", lampmodel);
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        lamp.Draw();
#endif


#if BOX == 1
        boxShader.Use();
        glm::mat4 boxtransformation;
        boxtransformation = glm::translate(boxtransformation, glm::vec3(0, 0, 0)); // translate it down so it's at the center of the scene
        boxtransformation = glm::scale(boxtransformation, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        boxShader.setMat4("model", boxtransformation);
        boxShader.setMat4("projection", projection);
        boxShader.setMat4("view", view);
        box.Draw();
#endif

#ifdef SKYBOX
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));   // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        map.Draw();
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
#endif


#ifdef NOTNEEDED
        lightShader.Use();
        lightShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightShader.setFloat("material.shininess", 32.0f);
        lightShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightShader.setVec3("light.specular", 0.5f, 0.5f, 0.5f);
        lightShader.setVec3("light.position", lightPos);
        lightShader.setVec3("viewPos", camera.Position);

        //view/projection transformation
        //projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
        //view = camera.GetViewMatrix();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        // world transformation

        model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down

        lightShader.setMat4("model", model);
        lightShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
#endif

        //light.Draw();

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
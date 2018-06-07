#include <glad\glad.h>
#include <GLFW\glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "box.h"
#include "CubeMap.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//windows size
const int width = 800;
const int height = 600;

// camera
Camera camera(glm::vec3(1.0f, 1.0f, 3.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("../shader.vs", "../shader.frag");
    Shader lightShader("../lighting.vs", "../lighting.frag");
    Shader lampShader("../lamp.vs", "../lamp.frag");
    //Shader skyboxShader("../cubemap.vs", "../cubemap.frag");


    Model ourModel("c:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\GLTF_MODEL\\duck\\Duck.gltf");
    //Model light("c:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\GLTF_MODEL\\Box\\Box.gltf");
    Model SuperModel("C:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\GLTF_MODEL\\centurion\\centurion.gltf");
    Box lamp;
    Box light;

    unsigned int cubemapTexture = loadCubemap(faces);

	while (!glfwWindowShouldClose(window))
	{
        ourShader.Use();
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
        //ourShader.setMat4("projection", projection);
        //ourShader.setMat4("view", view);


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
        lampmodel = glm::translate(lampmodel, lightPos); // translate it down so it's at the center of the scene
        lampmodel = glm::scale(lampmodel, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        //ourShader.setMat4("model", model);
        //ourModel.Draw(ourShader);

        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));	// it's a bit too big for our scene, so scale it down
        //ourShader.setMat4("model", model);
        //ourMode2.Draw(ourShader);
        lampShader.Use();
        lampShader.setMat4("model", lampmodel);
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        //lamp.Draw();
        SuperModel.Draw(ourShader);
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
        glm::mat4 model = glm::mat4();
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down

        lightShader.setMat4("model", model);
        lightShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

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

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
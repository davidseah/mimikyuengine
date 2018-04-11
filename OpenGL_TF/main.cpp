#include <iostream>
#include <vector>

//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>

//SOIL
#include <SOIL.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

using namespace std;

//Input Function Prototype
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

//Windows dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

//Camera 
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat yaw = -90.f;
GLfloat pitch = 0.0f;
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
GLfloat fov = 45.0f;


bool keys[1024];

GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TexCoords;
};

struct Texture
{
    GLuint id;
    string type;
};

class Mesh
{
    public:
    /*Mesh Data*/
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    /* Functions */
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    void Draw(Shader shader);

    private:
    /*Render data*/
    GLuint VAO, VBO, EBO;

    /* Functions*/
    void setupMesh();
};


int main()
{
    // Init GLFW
    glfwInit();
    
    //Set all the required option for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //Create a GLFWwindow object that we can use for GLFW's function
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //Tell GLFW that it should hide the cursor and capture it. 
    //Capturing a cursor means that once the application has focus the mouse cursor stays withthin the window
    //(unless the application loses focus or quits). We can do this with one simple configuration call
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Set this to true so GLEW knows to use a modern approach to retrieving functions pointer and extensions
    glewExperimental = GL_TRUE; //Ensure GLEW uses more modern techniques for manging OpenGL
    
    //Initialize GLEW to set up OpenGL Function pointers
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    Shader ourShader("../shader.vs", "../shader.frag");

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    // World space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //1. Bind Vertex Array Object
    glBindVertexArray(VAO);

    //2. Copy our vertices array in a buufer for OpengGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO


    GLuint texture1;
    GLuint texture2;
    // ===============================
    //Texture 1
    // ===============================
    //glGen Textures function first takes as input how many textures we want to generate
    //and stores them in a GLuint array as given as its second argument. 
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); //Set texture wrapping to GL_REPEAT

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texturewidth, textureheight;
    unsigned char* image = SOIL_load_image("../container.jpg", &texturewidth, &textureheight, 0, SOIL_LOAD_RGB);


    //Now that the texture is bound, we can start generating a texture using the previously loaded image data. 
    //Textures are generated with glTexImage2D
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth, textureheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    //Always a good practice to free the image memory and 
    //unbind the texture object
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    //===============================================
    //Texture 2
    //===============================================
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load create texture and generate mipmaps
    image = SOIL_load_image("../awesomeface.png", &texturewidth, &textureheight, 0, SOIL_LOAD_RGB);

    //Now that the texture is bound, we can start generating a texture using the previously loaded image data. 
    //Textures are generated with glTexImage2D
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturewidth, textureheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    //Always a good practice to free the image memory and 
    //unbind the texture object
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);


    while (!glfwWindowShouldClose(window))
    {
   

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Check and call events
        glfwPollEvents();
        do_movement();

        //Rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0); // Activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1); // Activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 1);

        ourShader.Use();

        GLfloat radius = 20.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraFront, cameraUp);
     
        glm::mat4 projection;

        //Note that we are translating the scene in the reverse direction of where we want to move
        projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projetcionLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projetcionLoc, 1, GL_FALSE, glm::value_ptr(projection));
   
        glBindVertexArray(VAO);

        
        glm::vec3 Direction;
        Direction.y = sin(glm::radians(pitch)) * cos(glm::radians(yaw));
        Direction.x = cos(glm::radians(pitch));
        Direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

        for (GLuint i = 0; i < 10; i++)
        {
            // Calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
	}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //when a user presses the escape key, we set the window should close 
    //property to true
    //closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (action == GLFW_PRESS)
    {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key] = false;
    }
}

void do_movement()
{
    //camera controls
    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keys[GLFW_KEY_W])
        cameraPos -= cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_S])
        cameraPos += cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_A])
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
   /* if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }*/

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
#pragma once

#include "Common.h"
#include "stb_image.h"
#include <glad\glad.h>
#include <iostream>


float planevertices[] =
{
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
    5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
    -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

    5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
    5.0f, -0.5f, -5.0f, 2.0f, 2.0f
};

class Plane
{
    public:
        Plane();
        void Draw();
     
    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int Texture;       
};


Plane::Plane()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planevertices), &planevertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    Texture = loadTexture("c:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\Resources\\Texture\\free_marble_texture_01designinstruct.jpg");
}

void Plane::Draw()
{
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}



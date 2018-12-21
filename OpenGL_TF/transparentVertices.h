#pragma once
#include "Common.h"
float transparentVertices[] = {
    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
    1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
    1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.5f, 0.0f, 1.0f, 0.0f
};

class TransparentVertices
{
public:
    TransparentVertices();
    void Draw();


private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int Texture;
};

TransparentVertices::TransparentVertices()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    //load textures
    Texture = loadTexture("c:\\Users\\uidj2545\\Desktop\\mimikyuengine\\mimikyuengine\\Resources\\Texture\\blending_transparent_window.png");
}

void TransparentVertices::Draw()
{
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
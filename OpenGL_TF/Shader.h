#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

class Shader
{
    public:
    //The Program ID
    GLuint Program;

    //Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void Use();
};


#endif
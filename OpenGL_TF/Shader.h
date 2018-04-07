#ifndef SHADER_H
#define SHADER_H

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

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
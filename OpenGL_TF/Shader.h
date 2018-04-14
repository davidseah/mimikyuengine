#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
    public:
    //The Program ID
    unsigned int ID;

    //Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//Use/activate the shader
    void Use();

	//utility unfirm functions
	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

};


#endif
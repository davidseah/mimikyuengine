#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string &name, float value1, float value2, float value3);
    void setVec3(const std::string &name, glm::vec3 value);
};


#endif
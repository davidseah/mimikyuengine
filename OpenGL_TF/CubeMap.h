#pragma once


#include <SOIL.h>
#include <glad\glad.h>

#include <vector>
#include <string>
#include <iostream>

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); ++i)
    {
        unsigned char *data = nullptr;
        try {
           data = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
        }
        catch (const std::overflow_error& e) {
            // this executes if f() throws std::overflow_error (same type rule)
        }
        catch (const std::runtime_error& e) {
            // this executes if f() throws std::underflow_error (base class rule)
        }
        catch (const std::exception& e) {
            // this executes if f() throws std::logic_error (base class rule)
        }
        catch (...) {
            // this executes if f() throws std::string or int or any other unrelated type
        }

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }
        SOIL_free_image_data(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    return textureID;
}
#version 330 core

//uniform vec4 ourColor; //We set this variable in the OpenGL code.
out vec4 FragColor;
in vec3 ourColor;

void main()
{
     FragColor = vec4(ourColor, 1.0f);
}

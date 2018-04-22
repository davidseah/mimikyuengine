#version 330 core

//uniform vec4 ourColor; //We set this variable in the OpenGL code.
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D texture2;

void main()
{
     FragColor = mix(texture(ourTexture, TexCoord), texture(texture2, TexCoord), 0.2);
}

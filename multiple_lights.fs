#version 330 core
out vec4 FragColor;

struct Material
{
	sampler2d diffuse;
	sampler2d specular;
	float shininess;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
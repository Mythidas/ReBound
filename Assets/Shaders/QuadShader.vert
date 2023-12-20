#version 450

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iColor;

layout (location = 0) out vec4 oColor;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_View;
	mat4 u_Projection;
};

void main()
{
	gl_Position = u_Projection * u_View * vec4(iPos, 1);
	oColor = vec4(iColor, 1);
}
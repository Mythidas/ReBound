#version 450

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iColor;

layout (location = 0) out vec4 oColor;

void main()
{
	gl_Position = vec4(iPos, 1);
	oColor = vec4(iColor, 1);
}
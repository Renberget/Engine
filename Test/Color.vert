#version 330 core

layout (location = 0) in vec2 iPos;
layout (location = 1) in vec4 iColor;

out vec4 color;

void main()
{
	color = iColor;
	gl_Position = vec4(iPos, 0.0, 1.0);
}

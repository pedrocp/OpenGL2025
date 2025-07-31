#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;


out vec4 color;
//uniform float time;
uniform mat4 camera;
uniform mat4 projection;

void main()
{
	color = vColor;
	gl_Position = projection * camera * vPosition;  //equivale a hacer return gl_Position
}

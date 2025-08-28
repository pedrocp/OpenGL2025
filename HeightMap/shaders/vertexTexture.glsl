#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;

out vec2 texCoord;

out vec4 color;

uniform float time;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 acumTrans;
uniform float frecuency;
uniform float amplitude;
uniform sampler2D height;

float F(float x, float z, float amplitude, float phase, float frecuency)
{
	return amplitude * cos(phase + frecuency * (x * x + z * z));
}

void main()
{
	vec4 newPosition = vPosition;

	vec4 color = texture(height, vTextCoord);
	newPosition.y = 0.3 * (0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b);
	texCoord = vTextCoord;

	gl_Position = 
		projection * 
		camera * 
		acumTrans * 
		newPosition;  //equivale a hacer return gl_Position
}

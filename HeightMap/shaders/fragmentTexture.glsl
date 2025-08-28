#version 460 core

in vec4 color;
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D diffuse;

void main()
{    
    vec4 texelColor = texture(diffuse, texCoord);

    fragColor = texelColor;
}

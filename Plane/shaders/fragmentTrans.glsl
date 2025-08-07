#version 460 core

in vec4 color;
out vec4 fragColor;

void main()
{
    vec4 frag = gl_FragCoord;
    if (distance(frag, vec4(0.0, 0.0f, 0.0f, 1.0f)) < 0.3)
        discard;
    else 
        fragColor = color;
}

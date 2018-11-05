#version 430

in vec3 vColorVS;

out vec4 outColor;

void main()
{
    outColor = vec4(vColorVS, 1);
}
#version 430

in vec3 vPos;
in vec3 vColor;

out vec3 vColorVS;

void main()
{
    vColorVS = vColor;    
    gl_Position = vec4(vPos, 1);
}
#version 430

#define VERTEX_ATTRIB_POS    0
#define VERTEX_ATTRIB_COLOR  1
#define VERTEX_ATTRIB_NORMAL 2

layout (location = VERTEX_ATTRIB_POS) in vec3 vPos;
layout (location = VERTEX_ATTRIB_COLOR) in vec3 vColor;

out vec3 vColorVS;

void main()
{
    vColorVS = vColor;    
    gl_Position = vec4(vPos, 1);
}
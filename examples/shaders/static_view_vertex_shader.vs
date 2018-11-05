#version 430

#define UNIFORM_MODEL          0
#define UNIFORM_VIEWPROJECTION 1

#define VERTEX_ATTRIB_POS    0
#define VERTEX_ATTRIB_COLOR  1

layout (location = UNIFORM_MODEL) uniform mat4 mModel;
layout (location = UNIFORM_VIEWPROJECTION) uniform mat4 mViewProjection;
layout (location = VERTEX_ATTRIB_POS) in vec3 vPos;
layout (location = VERTEX_ATTRIB_COLOR) in vec3 vColor;

out vec3 vColorVS;

void main()
{
    vColorVS = vColor;
    vec4 worldPos = mModel * vec4(vPos, 1);    
    gl_Position = mViewProjection * worldPos;
}